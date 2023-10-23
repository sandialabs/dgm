#ifndef DGM_AsciiFileIO_hpp
#define DGM_AsciiFileIO_hpp

/** \file AsciiFileIO.hpp
    \brief A basic interface to DGM ASCII file formats

    This interface supports 32 and 64 bit file IO through same the
    interface as binary files.

    \author K. Noel Belcourt
*/

// std includes
#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// system includes
#include <sys/stat.h>
#include <unistd.h>

// DGM includes
#include "CaseInsensitiveString.hpp"
#include "Format.hpp"
#include "Mesh.hpp"
#include "String.hpp"
#include "Topology.hpp"
#include "Utilities.hpp"

#ifdef DGM_PARALLEL

// boost includes
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/nonblocking.hpp>

#include <mpi.h>

namespace DGM {

/// given my rank, give me list of global element ids I own
template <typename Size>
std::pair<Size,Size> rank2gids(const Size gne, const int nprocs
  , const int rank)
{
  using std::pair;
  typedef pair<Size,Size> range_t;
  // implement with both contiguous and strided
  Size ne = gne / nprocs;
  // rank 0 number of elements
  Size rzne = gne - (nprocs-1) * ne;
  // base gid for this rank
  Size base = (0 == rank) ? 0 : rzne + (rank-1)*ne;
  // ne is number of elements on this rank
  if (0 == rank) ne = rzne;
  // range of gids [base, base+ne)
  return range_t(base, base+ne);
}

template <typename Size>
vector<Size> assign_global_ids(const Size gne, const int nprocs
  , const int rank)
{
  using std::pair;
  pair<int,int> r = rank2gids(gne, nprocs, rank);
  // number of elements on this rank
  Size ne = r.second - r.first;
  // use nrvo to elide the copy
  vector<Size> gids(ne, r.first);
  for (Size i=0; i<ne; ++i) gids[i] += i;
  return gids;
}

struct mpi_ascii_file {
  std::ifstream ifs;
  boost::mpi::communicator world;
  int rank, size;

  // interface for writing
  mpi_ascii_file(const std::string fname) : rank(0), size(1) {
    if (!file_exists(fname))
      throw runtime_error("Error: mpi_ascii_file can't open file " + fname);
    // read only on p0
    if (0 == rank) ifs.open(fname.c_str());
  }

  mpi_ascii_file(const std::string fname, boost::mpi::communicator w, bool)
    : world(w), rank(w.rank()), size(w.size())
  {
    using std::runtime_error;
    using std::string;
    using DGM::file_exists;
    // require file to be valid
    if (!file_exists(fname))
      throw runtime_error("Error: mpi_ascii_file can't open file " + fname);
    // read only on p0
    if (0 == rank) ifs.open(fname.c_str());
  }

  // interface for reading
  mpi_ascii_file(const std::string fname, boost::mpi::communicator w)
    : world(w), rank(w.rank()), size(w.size())
  {
    using std::runtime_error;
    using std::string;
    using DGM::file_exists;
    // require file to be valid
    if (!file_exists(fname))
      throw runtime_error("Error: mpi_ascii_file can't open file " + fname);
    // read only on p0
    if (0 == rank) ifs.open(fname.c_str());
  }

  ~mpi_ascii_file() {
    if (0 == rank) ifs.close();
  }

  void rewind() {
    // clear eof bit and seek to beginning of file
    ifs.clear();
    ifs.seekg(0, ifs.beg);
  }

  // only call send from p0
  template <typename SendIter, typename TargetIter
    , typename Local, typename Size>
  void send(SendIter s_it, TargetIter t_it, Local lne, const Size gne)
  {
    namespace mpi = boost::mpi;
    using std::distance;
    using std::copy;
    // copy my element types into place and advance to start non-root rank
    copy(s_it, s_it+lne, t_it);
    // nothing to do if serial
    if (1 == size) return;
    // if global number elements is local number, broadcast all data to all ranks
    Size ne = (gne - lne)/(size-1);
    if (gne != numeric_cast<Size>(lne)) {
      // skip past p0 data
      s_it += lne;
      lne = ne;
    }
    else {
      lne = gne;
    }
    // send element types to non-root ranks
    std::vector<mpi::request> sreq(size-1);
    for (int i=1; i<size; ++i, s_it+=ne)
      sreq[i-1] = world.isend(i, 1, &*s_it, lne);
    mpi::wait_all(sreq.begin(), sreq.end());
  }

  // must call receive on all non-root ranks
  template <typename Size, typename TargetIter>
  void receive(const Size lne, TargetIter t_it)
  {
    namespace mpi = boost::mpi;
    mpi::request rreq[1];
    if (1 == size) return;
    rreq[0] = world.irecv(0, 1, &*t_it, lne);
    mpi::wait_all(rreq, rreq+1);
  }

  // user specificed reduction operator (std::binary_function)
  template <typename Size, typename TargetIter, typename BinaryPredicate>
  void receive_reduce(const Size lne, TargetIter t_it, const BinaryPredicate op)
  {
    namespace mpi = boost::mpi;
    mpi::request rreq[1];
    if (1 == size) return;
    typedef typename iterator_traits<TargetIter>::value_type vt;
    vector<vt> lv(lne);
    rreq[0] = world.irecv(0, 1, &lv[0], lne);
    mpi::wait_all(rreq, rreq+1);
    for (int i=0; i<lne; ++i, ++t_it)
      *t_it = op(*t_it, lv[i]);
  }
};

struct inp_file : mpi_ascii_file {

  inp_file(const std::string fname, boost::mpi::communicator w)
    : mpi_ascii_file(fname, w) {
  }

  // note: input value (i) is unchanged if parameter not found
  void find_inp_value(const case_insensitive_string s, int& i) {
    string buffer;
    // look for input starting at top of file
    rewind();
    // search for parameter
    while (ifs.good() && !ifs.eof()) {
      ifs >> buffer;
      if (s == buffer) {
        ifs >> buffer >> i;
        break;
      }
      // read to end of line
      getline(ifs, buffer);
    }
  }

  void get_bmesh(int& bmesh) {
    namespace mpi = boost::mpi;
    if (0 == rank) find_inp_value("bmesh", bmesh);
    mpi::broadcast(world, bmesh, 0);
  }

  void get_physics(int& physics) {
    namespace mpi = boost::mpi;
    if (0 == rank) find_inp_value("eqntype", physics);
    mpi::broadcast(world, physics, 0);
  }

  void get_porder(int& porder) {
    namespace mpi = boost::mpi;
    if (0 == rank) find_inp_value("p", porder);
    mpi::broadcast(world, porder, 0);
  }
};

// eqntype
inline void get_physics(int& physics, inp_file& inf) {
  inf.get_physics(physics);
}

// if no default porder, value is unchanged
inline void get_porder(int& porder, inp_file& inf) {
  inf.get_porder(porder);
}

struct con_file : mpi_ascii_file {

  con_file(const std::string fname, boost::mpi::communicator w)
    : mpi_ascii_file(fname, w) {
  }

  template <typename Size>
  std::vector<Size> connectivity(const Size gne) {
    using std::pair;
    using std::vector;
    namespace mpi = boost::mpi;
    vector<Size> conn;
    if (0 == rank) {
      using std::string;
      using std::ws;
      // skip connectivity header
      string strbuf;
      getline(ifs, strbuf);
      getline(ifs, strbuf);
      // read connectivity records
      Size first, second, first_face, second_face;
      char c;
      while (ifs.good() && !ifs.eof()) {
        ifs >> c >> first >> first_face >> second >> second_face >> ws;
        conn.push_back(first);
        conn.push_back(first_face);
        conn.push_back(second);
        conn.push_back(second_face);
      }
    }
    mpi::broadcast(world, conn, 0);
    return conn;
  }

  template <typename ElemIter, typename Size>
  std::vector< std::pair<Size,Size> >
  connectivity(const ElemIter e_it, const ElemIter e_end, const Size gne
    , const Size nsd)
  {
    using std::pair;
    using std::vector;
    namespace mpi = boost::mpi;
    vector< pair<Size,Size> > conn;
    if (0 == rank) {
      using std::string;
      using std::ws;
      typedef pair<Size, Size> range_t;
      // over-allocate connectivity to avoid resizing
      // max of 6 sides per element (hex) for 3d, 4 (quad) for 2d
      conn.reserve(gne * ((3 == nsd) ? 6 : 4));
      // skip connectivity header
      string strbuf;
      getline(ifs, strbuf);
      getline(ifs, strbuf);
      // read connectivity records
      Size first, second, dummy;
      unsigned int i = 0;
      char c;
      while (ifs.good() && !ifs.eof()) {
        ifs >> c >> first >> dummy >> second >> dummy >> ws;
        conn.push_back(pair<Size,Size>(first,second));
        ++i;
      }
      // shrink to fit
      vector< pair<Size,Size> >(conn.begin(), conn.begin()+i).swap(conn);
      // if serial, we're done
      if (1 == size) return conn;
      // get gids I own
      range_t r = rank2gids(gne, size, 0);
      // find starting point for p1
      typename vector<pair<Size,Size> >::iterator p_it = conn.begin(), p_end;
      while ((*p_it).first < r.second) ++p_it;
      typename vector<pair<Size,Size> >::iterator p0_end = p_it;
      // send connectivity to other processors
      std::vector<mpi::request> dreq(size-1);
      for (int i=1; i<size; ++i) {
        // figure out which connectivity records owned by ith rank
        r = rank2gids(gne, size, i);
        p_end = p_it;
        while (p_end != conn.end() && (*p_end).first < r.second) ++p_end;
        // send data to other ranks, first #connectivity records, 2nd is data
        // send data to ith rank [p_it,p_end)
        int ne = distance(p_it, p_end);
        mpi::request sreq = world.isend(i, 1, ne);
        sreq.wait();
        dreq[i-1] = world.isend(i, 2, &*p_it, ne);
        // advance to next ranks data
        p_it = p_end;
      }
      mpi::wait_all(dreq.begin(), dreq.end());
      // resize so valid for p0
      conn.erase(p0_end, conn.end());
    }
    else {
      // receive length of connectivity and data from rank 0
      mpi::request rreq;
      // get number of connectivity records
      int lne = 0;
      rreq = world.irecv(0, 1, lne);
      rreq.wait();
      // now know how many connectivity records, resize
      conn.resize(lne);
      rreq = world.irecv(0, 2, &*conn.begin(), lne);
      rreq.wait();
    }
    return conn;
  }
};

struct crv_file : mpi_ascii_file {

  crv_file(const std::string fname, boost::mpi::communicator w)
    : mpi_ascii_file(fname, w) {
  }

  template <typename ElemIter, typename CurveIter, typename Size>
  void get_element_curvature(const ElemIter e_it, const ElemIter e_end
    , CurveIter c_it, const Size gne)
  {
    using std::distance;
    // only read file on p0
    if (0 == rank) {
      using std::getline;
      using std::string;
      // skip header
      string strbuf;
      getline(ifs, strbuf);
      int nct = 0; // number of curve types
      ifs >> nct;
      getline(ifs, strbuf);
      for (int i=0; i<nct; ++i) {
        getline(ifs, strbuf);
        getline(ifs, strbuf);
        getline(ifs, strbuf);
      }
      // number of curved elements
      int nce = 0;
      ifs >> nce;
      getline(ifs, strbuf);
      // assume all affine elements (true)
      vector<int> eids(gne, 1);
      int eid = 0;
      int is_affine = 0;
      for (int i=0; i<nce; ++i) {
        ifs >> eid >> is_affine >> strbuf;
        eids[eid] = is_affine;
      }
      // send element curvatures to other processors
      send(eids.begin(), c_it, distance(e_it, e_end), gne);
    }
    else {
      // receive weights from rank 0
      receive(distance(e_it, e_end), c_it);
    }
  }
};

template <typename ElemIter, typename CurveIter, typename Size>
void get_element_curvature(const ElemIter e_it, const ElemIter e_end
  , CurveIter c_it, const Size gne, crv_file& cf) {
  cf.get_element_curvature(e_it, e_end, c_it, gne);
}

struct wgt_file : mpi_ascii_file {

  wgt_file(const std::string fname, boost::mpi::communicator w)
    : mpi_ascii_file(fname, w) {
  }

  template <typename ElemIter, typename WgtIter>
  void read_weights(const ElemIter e_it, const ElemIter e_end, WgtIter w_it) {
    using std::distance;
    // read only on p0
    if (0 == rank) {
      using std::copy;
      using std::iterator_traits;
      typedef typename iterator_traits<ElemIter>::value_type Size;
      typedef typename iterator_traits<WgtIter>::value_type WgtType;
      // read global number of elements
      Size gne = 0;
      ifs >> gne;
      // read all element weights
      vector<WgtType> wgts(gne);
      for (Size i=0; i<gne; ++i) ifs >> wgts[i];
      // pass my local number of elements into send
      send(wgts.begin(), w_it, distance(e_it, e_end), gne);
    }
    else {
      // receive weights from rank 0
      receive(distance(e_it, e_end), w_it);
    }
  }
};

struct msh_file : mpi_ascii_file {

  int m_gne, m_nsd;

  // interface for reading
  msh_file(const std::string fname, boost::mpi::communicator w)
    : mpi_ascii_file(fname, w), m_gne(0), m_nsd(0)
  {
    if (0 == rank) {
      using std::getline;
      using std::string;
      string strbuf;
      getline(ifs, strbuf);
      ifs >> m_gne >> m_nsd;
      rewind();
    }
  }

  template <typename Size>
  void get_global_number_elements(Size& gne) {
    namespace mpi = boost::mpi;
    // ensure consistent return
    if (0 == rank) gne = m_gne;
    mpi::broadcast(world, gne, 0);
  }

  template <typename Size>
  void get_number_space_dimensions(Size& nsd) {
    namespace mpi = boost::mpi;
    // ensure consistent return
    if (0 == rank) nsd = m_nsd;
    mpi::broadcast(world, nsd, 0);
  }

  template <typename ElementIter, typename ElemTypeIter>
  void get_element_types(const ElementIter it, const ElementIter end
    , ElemTypeIter e_it)
  {
    using std::distance;
    if (0 == rank) {
      // only read file on p0
      using std::copy;
      using std::getline;
      using std::iterator_traits;
      using std::string;
      using std::vector;
      // typedef typename iterator_traits<ElementIter>::value_type Size;
      typedef typename iterator_traits<ElemTypeIter>::value_type eType;
      // skip comment line
      string strbuf;
      getline(ifs, strbuf);
      getline(ifs, strbuf);
      // read element type as string, convert to enum
      vector<eType> ets(m_gne);
      int dummy = 0;
      for (int i=0; i<m_gne; ++i) {
        ifs >> strbuf >> dummy >> strbuf;
        // convert to element enum
        ets[i] = DGM::Topology::string2ElementType(strbuf.c_str());
        getline(ifs, strbuf);  // skip rest of line
        // skip coordinates
        for (int j=0; j<m_nsd; ++j)
          getline(ifs, strbuf);
      }
      // send data to non-root ranks, pass in my local number of elements
      send(ets.begin(), e_it, distance(it, end), m_gne);
    }
    else {
      // receive weights from rank 0
      receive(distance(it, end), e_it);
    }
  }

  // assume 3d for now
  template <typename ElemIter, typename CoordIter>
  void get_coordinates(ElemIter, ElemIter, CoordIter x_it
    , CoordIter y_it, CoordIter z_it)
  {
    using DGM::Mesh;
    using DGM::Topology::ElementType;
    using DGM::Topology::string2ElementType;
    using std::iterator_traits;
    using std::streamoff;
    using std::string;
    typedef typename iterator_traits<ElemIter>::value_type Size;
    ElementType et;
    string buf, etype;
    Size nv = 0;
    // start at beginning
    rewind();
    getline(ifs, buf);
    getline(ifs, buf);
    for (int i=0; i<m_gne; ++i) {
      ifs >> buf >> buf >> etype;
      // convert to element enum
      et = string2ElementType(etype.c_str());
      nv = Mesh::nodes[et];
      getline(ifs, buf);  // skip rest of line
      // x coordinates
      for (Size k=0; k<nv; ++k, ++x_it) {
        ifs >> *x_it;
      }
      // y coordinates
      if (1 < m_nsd) {
        for (Size k=0; k<nv; ++k, ++y_it) {
          ifs >> *y_it;
        }
        // z coordinates
        if (2 < m_nsd) {
          for (Size k=0; k<nv; ++k, ++z_it) {
            ifs >> *z_it;
          }
        }
      }
    }
  }
};

// ascii mesh (msh) file interface
template <typename Size>
void get_number_space_dimensions(Size& nsd, msh_file& mf) {
  mf.get_number_space_dimensions(nsd);
}

template <typename Size>
void get_global_number_elements(Size& gne, msh_file& mf) {
  mf.get_global_number_elements(gne);
}

template <typename ElemIter, typename CoordIter>
void get_coordinates(ElemIter e_it, ElemIter e_end, CoordIter x_it
  , CoordIter y_it, CoordIter z_it, msh_file& mf)
{
  mf.get_coordinates(e_it, e_end, x_it, y_it, z_it);
}

template <typename ElementIter, typename ElementTypeIter>
void get_element_types(const ElementIter it, const ElementIter end
  , ElementTypeIter e_it, msh_file& mf)
{
  mf.get_element_types(it, end, e_it);
}

// ascii weights file interface
template <typename ElemIter, typename WgtIter>
void get_element_weights(const ElemIter e_it, const ElemIter e_end
  , WgtIter w_it, wgt_file& wf)
{
  wf.read_weights(e_it, e_end, w_it);
}

struct ord_file : mpi_ascii_file {

  ord_file(const std::string fname, boost::mpi::communicator w)
    : mpi_ascii_file(fname, w) {
  }

  // for reducing received porder from p0
  struct non_zero_order : public std::binary_function<int, int, int> {
    // second argument (y) is data passed from p0
    int operator()(int x, int y) const {
      // use y if non-zero, otherwise x
      return 0 != y ? y : x;
    }
  };

  template <typename ElemIter, typename pOrderIter, typename Size>
  void get_element_porder(const ElemIter e_it, const ElemIter e_end
    , pOrderIter p_it, const Size gne)
  {
    // read ascii order file to override values in binary file
    if (0 == rank) {
      using std::string;
      using std::vector;
      // skip first line
      string strbuf;
      int e, o, dummy;
      getline(ifs, strbuf);
      // don't know how many entries are in order file
      vector<int> po(gne, 0);
      while (ifs.good() && !ifs.eof()) {
        ifs >> e >> o >> dummy;
        po[e] = o;
      }
      // send element porders to other processors
      send(po.begin(), p_it, distance(e_it, e_end), gne);
    }
    else {
      // receive weights from rank 0
      // since we may not receive updated values for all elements
      // as order file may only have a few values in it, we pick
      // the largest from the existing and received data
      receive_reduce(distance(e_it, e_end), p_it, non_zero_order());
    }
  }
};

template <typename ElemIter, typename pOrderIter, typename Size>
void get_element_porder(const ElemIter e_it, const ElemIter e_end
  , pOrderIter p_it, const Size gne, ord_file& of)
{
  of.get_element_porder(e_it, e_end, p_it, gne);
}

template <typename Size>
std::vector<Size>
get_connectivity(const Size gne, con_file& cf)
{
  // uses rvo
  return cf.connectivity(gne);
}

template <typename ElemIter, typename Size>
std::vector< std::pair<Size,Size> >
get_connectivity(const ElemIter e_it, const ElemIter e_end, const Size gne
  , const Size nsd, con_file& cf)
{
  // uses rvo
  return cf.connectivity(e_it, e_end, gne, nsd);
}

}  // namespace DGM

#else  // DGM_PARALLEL

namespace DGM {

struct con_file {
  std::ofstream ofs;
  template <typename Size>
  con_file(const std::string fname, Size ne) {
    ofs.open(fname.c_str());
    ofs << "# CONNECTIVITY DATA\n";
    ofs << ne << " ne\n";
  }
};

template <typename Iterator>
void write_connectivity(Iterator it, Iterator end, con_file& cf) {
  for (; it != end; ++it) {
    cf.ofs << "E\t" << (*it).eid << "\t" << (*it).side << "\t"
      << (*it).leid << "\t" << (*it).lside << "\n";
  }
}

struct msh_file {

  std::ofstream ofs;
  Size m_gne, m_nsd;

  // interface for writing
  msh_file(const std::string fname, Size nsd, Size ne) :
    m_gne(ne), m_nsd(nsd)
  {
    ofs.open(fname.c_str());
    ofs << "# MESH DATA \n";
    ofs << ne << " " << nsd << " NE NSD\n";
  }
};

// interfaces for writing msh file
template <typename Iterator, typename Eiterator>
void write_coordinates(Iterator it, Iterator end, 
  Eiterator ei, msh_file& mf)
{
  typedef std::numeric_limits<Scalar> dbl;
  DGM::Format sci(dbl::digits10);
  sci.scientific().width(dbl::digits10);
  using std::iterator_traits;
  for (Size eid=0; eid<mf.m_gne; ++eid, ++ei) {
    unsigned int nv = num_vertices(*ei);
    mf.ofs << "ELEMENT " << eid << "  " << topology_name(*ei) << '\n';
    Iterator tmp = it;
    for (; it != tmp+nv; ++it) {
      mf.ofs << ' ' << sci((*it).x) << ' ';
    }
    mf.ofs << '\n';
    if (1 < mf.m_nsd) {
      for (it = tmp; it != tmp+nv; ++it) {
        mf.ofs << ' ' << sci((*it).y) << ' ';
      }
      mf.ofs << '\n';
      if (2 < mf.m_nsd) {
        for (it = tmp; it != tmp+nv; ++it) {
          mf.ofs << ' ' << sci((*it).z) << ' ';
        }
        mf.ofs << '\n';
      }
    }
  }
}

} // namespace DGM

#endif  // DGM_PARALLEL

#endif // DGM_AsciiFileIO_hpp
