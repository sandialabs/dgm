#ifndef DGM_MESH_HPP
#define DGM_MESH_HPP

/** \file Mesh.hpp
    \brief Simple rectilinear mesh generator declaration
    \author S. Scott Collis
    \author Tom Smith
*/

// system includes
#include <iostream>
#include <limits>
#include <vector>
#include <string>
using namespace std;

// TPL includes
#ifdef DGM_USE_JSON
#include "json/json.h"
#endif

// DTK includes
#include "DTK.hpp"

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#endif
#include "Topology.hpp"
#include "Types.hpp"
#include "Partition.hpp"
#include "Table.hpp"
#include "Coordinates.hpp"
#include "Constants.hpp"

namespace DGM {

/// DGM Mesh generation class
/** This class can build a mesh both from an input file as well as simple
    rectilinear meshes from an input parameter table. In the future, it
    would be a good idea for this to derive off of a generic BaseMesh (see
    above) and then have specific instances for a FileMesh or
    RectilinearMesh.
*/
class Mesh : public DTK::Mesh {

public:

  typedef DGM::Size GlobalSize;
  typedef DGM::Ordinal LocalSize;

private:

  Comm::Ptr comm;               ///< Communicator for this mesh

  /// Partition for parallel computing
  Partition<Size,Ordinal,Scalar>::Ptr partition;

  static const Scalar slop;     ///< If set, should be machine EPSILON

  /// Modulo function
  template <typename T>
  static T mod(const T x, const T y);

  static const Scalar EPSILON;  ///< Tolerance for element identification

public:
  
  // set default values for Mesh parameters
  static void setDefaults(Table &params) {
    params.get("nsd",1);            // number of space dimensions
    params.get("Lx",1.0);           // domain length in x
    params.get("Ly",1.0);           // domain length in y
    params.get("Lz",1.0);           // domain length in z
    params.get("nx",4);             // number of elements in x
    params.get("ny",4);             // number of elements in y
    params.get("nz",4);             // number of elements in z
    params.get("x0",0.0);           // offset in x
    params.get("y0",0.0);           // offset in y
    params.get("z0",0.0);           // offset in z
    params.get("Cx",0.0);           // stretch factor in x
    params.get("Cy",0.0);           // stretch factor in y
    params.get("Cz",0.0);           // stretch factor in z
    params.get("Dx",0);             // stretch direction in x
                                    //   (-1=left, 0=left&right, 1=right)
    params.get("Dy",0);             // stretch direction in y
    params.get("Dz",0);             // stretch direction in z
    params.get("phi",0.0);          // rotation about z-axis
    params.get("theta",0.0);        // rotation about y-axis
    params.get("root","new");       // root file name for output
    params.get("verb",0);           // verbosity level
    params.get("tecplot",0);        // output a tecplot file
    params.get("layers","");        // layers file
    params.get("ascii",1);          // use ASCII output file
    params.get("binary",1);         // output binary mesh file
    params.get("info",0);           // output mesh information
    params.get("nodal",false);      // use nodal elements
    params.get("spectral",false);   // use spectral elements
    params.get("periodic",true);    // use periodic mesh
    params.get("graph",true);       // output graph and weights
    params.get("pencils",false);    // vertical element numbering
    params.get("tri",0);            // tri mesh generation is off
    params.get("low-memory",false); // low memory mesh generation is off
  }

  /// Simple side connectivity class
  /** This is a very simple connectivity class that helps support the
      DGM::Mesh generator. */
  template <typename GlobalSize, typename LocalSize>
  class Con {
  public:
    GlobalSize eid;                      ///< Global Element id
    LocalSize  side;                     ///< Local Side id
    GlobalSize leid;                     ///< Linked global element id
    LocalSize  lside;                    ///< Linked side id
    GlobalSize gid;                      ///< Global side id

    template <typename Target, typename Source>
    static Target smart_cast(Source arg) {
      if (defined(arg)) return numeric_cast<Target>(arg);
      return numeric_limits<Target>::max();
    }

    /// Con(nectivity) constructor
    Con(const GlobalSize e=undefined<GlobalSize>(),
        const LocalSize s=undefined<LocalSize>(),
        const GlobalSize le=undefined<GlobalSize>(),
        const LocalSize ls=undefined<LocalSize>(),
        const GlobalSize i=undefined<GlobalSize>()) :
      eid(e), side(s), leid(le), lside(ls), gid(i) {}

    Con(const Con<int, int> &in) :
      eid(smart_cast<GlobalSize>(in.eid)),
      side(smart_cast<LocalSize>(in.side)),
      leid(smart_cast<GlobalSize>(in.leid)),
      lside(smart_cast<LocalSize>(in.lside)),
      gid(smart_cast<GlobalSize>(in.gid)) { }

    Con(const Con<unsigned int, unsigned int> &in) :
      eid(smart_cast<GlobalSize>(in.eid)),
      side(smart_cast<LocalSize>(in.side)),
      leid(smart_cast<GlobalSize>(in.leid)),
      lside(smart_cast<LocalSize>(in.lside)),
      gid(smart_cast<GlobalSize>(in.gid)) { }

    Con(const Con<long long, int> &in) :
      eid(smart_cast<GlobalSize>(in.eid)),
      side(smart_cast<LocalSize>(in.side)),
      leid(smart_cast<GlobalSize>(in.leid)),
      lside(smart_cast<LocalSize>(in.lside)),
      gid(smart_cast<GlobalSize>(in.gid)) { }

    Con(const Con<long long, long long> &in) :
      eid(smart_cast<GlobalSize>(in.eid)),
      side(smart_cast<LocalSize>(in.side)),
      leid(smart_cast<GlobalSize>(in.leid)),
      lside(smart_cast<LocalSize>(in.lside)),
      gid(smart_cast<GlobalSize>(in.gid)) { }

    Con(const Con<long, int> &in) :
      eid(smart_cast<GlobalSize>(in.eid)),
      side(smart_cast<LocalSize>(in.side)),
      leid(smart_cast<GlobalSize>(in.leid)),
      lside(smart_cast<LocalSize>(in.lside)),
      gid(smart_cast<GlobalSize>(in.gid)) { }

    Con(const Con<unsigned long, int> &in) :
      eid(smart_cast<GlobalSize>(in.eid)),
      side(smart_cast<LocalSize>(in.side)),
      leid(smart_cast<GlobalSize>(in.leid)),
      lside(smart_cast<LocalSize>(in.lside)),
      gid(smart_cast<GlobalSize>(in.gid)) { }

    Con(const Con<long, long> &in) :
      eid(smart_cast<GlobalSize>(in.eid)),
      side(smart_cast<LocalSize>(in.side)),
      leid(smart_cast<GlobalSize>(in.leid)),
      lside(smart_cast<LocalSize>(in.lside)),
      gid(smart_cast<GlobalSize>(in.gid)) { }

    Con(const Con<unsigned long long, int> &in) :
      eid(smart_cast<GlobalSize>(in.eid)),
      side(smart_cast<LocalSize>(in.side)),
      leid(smart_cast<GlobalSize>(in.leid)),
      lside(smart_cast<LocalSize>(in.lside)),
      gid(smart_cast<GlobalSize>(in.gid)) { }

    Con(const Con<unsigned long, unsigned long> &in) :
      eid(smart_cast<GlobalSize>(in.eid)),
      side(smart_cast<LocalSize>(in.side)),
      leid(smart_cast<GlobalSize>(in.leid)),
      lside(smart_cast<LocalSize>(in.lside)),
      gid(smart_cast<GlobalSize>(in.gid)) { }

    Con(const Con<unsigned long long, unsigned long long> &in) :
      eid(smart_cast<GlobalSize>(in.eid)),
      side(smart_cast<LocalSize>(in.side)),
      leid(smart_cast<GlobalSize>(in.leid)),
      lside(smart_cast<LocalSize>(in.lside)),
      gid(smart_cast<GlobalSize>(in.gid)) { }

#ifdef DGM_USE_MESH_CON_CASTS
    /// Cast operator
    operator Con<unsigned,int>() {
      return Con<unsigned,int>(eid,side,leid,lside,gid);
    }

    /// Cast operator
    operator Con<unsigned long,int>() {
      return Con<unsigned long,int>(eid,side,leid,lside,gid);
    }

    /// Cast operator
    operator Con<unsigned long long,int>() {
      return Con<unsigned long long,int>(eid,side,leid,lside,gid);
    }

    /// Cast operator
    operator Con<long long,int>() {
      return Con<long long,int>(eid,side,leid,lside,gid);
    }

    /// Cast operator
    operator Con<long long,long long>() {
      return Con<long long,long long>(eid,side,leid,lside,gid);
    }

    /// Cast operator
    operator Con<unsigned long long,unsigned long long>() {
      return Con<unsigned long long,unsigned long long>
        (eid,side,leid,lside,gid);
    }
#endif
    /// Size of Con object
    static size_t size() { return sizeof(Con); }

    /// General undefined id
    template <typename T>
    static T undefined() { return numeric_limits<T>::max(); }

    /// Test if undefined id
    template <typename T>
    static bool undefined(const T id) { return id==undefined<T>(); }

    /// Test if defined id
    template <typename T>
    static bool defined(const T id) { return !undefined<T>(id); }

    /// Equality operator
    Con & operator= (const Con &in) {
      if (this==&in) return *this;
      eid=in.eid; side=in.side; leid=in.leid; lside=in.lside; gid=in.gid;
      return *this;
    }

    /// Reset the connectivity
    Con & set(const GlobalSize ieid, const LocalSize iside,
              const GlobalSize ileid, const LocalSize ilside,
              const GlobalSize igid=undefined<GlobalSize>()) {
      //cout << igid << endl;
      eid=ieid; side=iside; leid=ileid; lside=ilside; gid=igid;
      return *this;
    }

    /// comparison x less then y
    friend bool operator<(const Con &x, const Con &y) {
      if (x.eid < y.eid) return true;
      else if (x.eid > y.eid) return false;
      else if (x.side < y.side) return true;
      else if (x.side > y.side) return false;
      return false;
    }

    /// comparison equality
    bool operator==(const Con &other) const {
      if (eid == other.eid && side == other.side) {
        if (leid != other.leid || lside != other.lside || gid != other.gid)
          throw DGM::exception("Incompatible connections");
        return true;
      }
      return false;
    }

    /// comparison not equal
    bool operator!=(const Con &other) const {
      return (!operator==(other));
    }

    /// Output connectivity to a stream
    friend ostream & operator<< (ostream &os, const Con &con) {
      os << "e" << con.eid << "s" << con.side << "->e"
         << con.leid << "s" << con.lside;
      if (defined(con.gid)) os << ":" << con.gid;
      return os;
    }
  };

  /// Number of element types
  static const unsigned NumEtype = DGM::Topology::NumElementTypes;

  static const unsigned nodes[NumEtype]; ///< # of nodes for each element type
  static const unsigned sides[NumEtype]; ///< # of sides for each element type

  typedef Con<GlobalSize,LocalSize> MyCon;

  LocalSize nsd;                ///< Number of space dimensions
  GlobalSize ne;                ///< Number of elements
  int nx;                       ///< Number of cells in x-direction
  int ny;                       ///< Number of cells in y-direction
  int nz;                       ///< Number of cells in z-direction
  Scalar x0;                    ///< Lower lefthand corner
  Scalar y0;                    ///< Lower lefthand corner
  Scalar z0;                    ///< Lower lefthand corner
  Scalar Lx;                    ///< Domain size in x
  Scalar Ly;                    ///< Domain size in y
  Scalar Lz;                    ///< Domain size in z
  Scalar dx;                    ///< Mesh space in x
  Scalar dy;                    ///< Mesh space in y
  Scalar dz;                    ///< Mesh space in z
  Scalar Cx;                    ///< Stretching factors (0=uniform)
  Scalar Cy;                    ///< Stretching factors (0=uniform)
  Scalar Cz;                    ///< Stretching factors (0=uniform)
  int Dx;                       ///< Stretch (-1=left,0=left&right,1=right)
  int Dy;                       ///< Stretch (-1=left,0=left&right,1=right)
  int Dz;                       ///< Stretch (-1=left,0=left&right,1=right)
  Scalar theta;                 ///< Rotation angle about y-axis
  Scalar phi;                   ///< Rotation angle about z-axis
  vector<Point> point;          ///< Mesh points
  vector<MyCon> con;            ///< Connectivity
  vector<Topology::ElementType> etype;     ///< Element type
  vector<size_t> indices;       ///< Where in point is first node of element
  vector<bool> crv_els;         ///< curved element: 0=false, 1=true
  const bool nodal;             ///< Output nodal elements
  const bool spectral;          ///< Output spectral elements
  const bool periodic;          ///< Output a periodic mesh   
  const bool verbose;           ///< Verbosity flag

  /// Default constructor
  Mesh(const LocalSize NSD=0, const GlobalSize NE=0,
       const DGM::Comm::Ptr COMM=DGM::Comm::World) :
    comm(COMM), partition(), nsd(NSD), ne(NE), nx(0), ny(0), nz(0), x0(0.0),
    y0(0.0), z0(0.0), Lx(0.0), Ly(0.0), Lz(0.0), dx(0.0), dy(0.0), dz(0.0),
    Cx(0.0), Cy(0.0), Cz(0.0), Dx(0.0), Dy(0.0), Dz(0.0), theta(0.0), phi(0.0),
    nodal(false), spectral(false), periodic(true), verbose(false) {}

  /// File constructor
  Mesh(const string &, const int verb=0,
       const DGM::Comm::Ptr COMM=DGM::Comm::World);

  /// Primary constructor
  Mesh(Table &, iVector ed=iVector(), dVector d=dVector(),
       vector<string> f=vector<string>(), const bool Nodal=false,
       const bool Spectral=false, const bool Periodic=true,
       const int verb=0, const DGM::Comm::Ptr COMM=DGM::Comm::World);

  template <typename T>
  static T undefined() {
    return MyCon::undefined<T>();
  }

  template <typename T>
  static T undefined(const T id) {
    return MyCon::undefined<T>(id);
  }

  template <typename T>
  static T defined(const T id) {
    return MyCon::defined<T>(id);
  }

  /// Setup for parallel
  void setup_parallel
  (const Comm::Ptr comm_,
   const Partition<GlobalSize,LocalSize,Scalar>::Ptr partition_) {
    comm = comm_;
    partition = partition_;
  }

  /// make sure that parallel is setup
  bool valid_parallel() const {
    if (comm.get() != 0 && partition.get() != 0 ) return true;
    return false;
  }

  /// Find the elements for a given point in 2d
  Size find_source_elem(Point pnode, Size *elemindex, const int verb=0);

  /// Find the elements for a given point in 1d
  Size find_source_elem_1d(Point pnode, Size *elemindex);

  /// Find the elements for a given point in 2d
  Size find_source_elem_2d(Point pnode, Size *elemindex);

  /// Find the elements for a given point in 3d
  Size find_source_elem_3d(Point pnode, Size *elemindex);

  /// Return axis aligned bounding boxes for every element in the mesh.
  void boxes(vector< vector<float> > &bounds);

  /// Computes the bounding box for a given element
  vector<float> box(const Size element_number);

  /// Tells if the given point is in the given element.
  bool is_in_element(const Scalar * const point,
                     const size_t element_number) ;

  /// Helper function to find the min/max bounds for a range of values
  void check_bounds(const Scalar coord, Scalar &min, Scalar &max) const;

  /// Resize a mesh
  void resize(LocalSize NSD, GlobalSize NE) { nsd=NSD; ne=NE; }

  /// Get the number of points
  size_t numPoints() const { return point.size(); }

  /// Get the number of space dimensions
  LocalSize numSpaceDims() const { return nsd; }

  /// Accessor for communicator
  DGM::Comm::Ptr get_comm() const { return comm; }

  /// Accessor for partition
  DGM::Partition<GlobalSize,LocalSize,Scalar>::Ptr get_partition() const {
    return partition;
  }

  /// Return the size of your Con object
  size_t con_size() const { return MyCon::size(); }

  /// \name Mesh I/O functions
  //@{
  streamoff write_header(const string &, const streamoff offset=0) const;
  streamoff read_header(const string &, Json::Value &root,
                        const streamoff offset=0);
  streamoff write(const string &, const streamoff offset=0) const;
  streamoff write(const string &fname, const streamoff offset,
                  const Json::Value &header);
  streamoff read(const string &, const streamoff offset=0);
  streamoff read(const string &fname, const streamoff offset,
                 const Json::Value &header);
  streamoff write_connectivity(const string &, const streamoff offset=0) const;
  streamoff read_connectivity(const string &, const streamoff offset=0);
  streamoff read_connectivity(const string &, const streamoff offset,
                              const Json::Value &header);
  void write_curve(const string &) const;
#ifdef DGM_PARALLEL
  MPI_Offset MPI_write(const Comm::Ptr,
                       const Partition<Size,Ordinal,Scalar>::Ptr,
                       const string &, const MPI_Offset offset=0) const;
  MPI_Offset MPI_read(const Comm::Ptr,
                      const Partition<Size,Ordinal,Scalar>::Ptr,
                      const string &, const MPI_Offset offset=0);
  MPI_Offset MPI_read_connectivity(const Comm::Ptr,
                                   const Partition<Size,Ordinal,Scalar>::Ptr,
                                   const string &, const MPI_Offset offset=0);
  MPI_Offset MPI_write_connectivity(const Comm::Ptr,
                                    const Partition<Size,Ordinal,Scalar>::Ptr,
                                    const string &,
                                    const MPI_Offset offset=0) const;
#endif
  //@}

  /// \name Mesh streams
  //@{
  inline friend ostream &operator<<(ostream &, const Mesh &);
  //@}

  /// \name Helper functions
  //@{

  static Scalar get_phase_angle(const Scalar x, const Scalar y);

  /// Distribute points either uniformly (cs==0) or stretched on a line
  inline static Scalar distribute( const Scalar Lx, const Scalar cs,
                                   const Size nx, const  Size i,
                                   const Scalar x0=0.0, const int ds=0 ) {
    if (cs==0) return x0 + i*Lx/(nx-1);
    if (ds==-1)
      return x0 + Lx * ( 1.0 - tanh( cs*Scalar((nx-1)-i)/(nx-1) )/tanh( cs ) );
    else if (ds== 0)
      return x0 + 0.5*Lx*tanh(cs*(i*2.0/(nx-1)-1.0))/tanh(cs) + 0.5*Lx;
    else if (ds== 1)
      return x0 + Lx*tanh( cs*Scalar(i)/(nx-1) )/tanh( cs );
    else if (ds== 2) {
      const Scalar Lxb2 = Lx/2.0;
      const Size nxb2  = (nx-1)/2;
      Size nxb2r = nxb2;
      if (2*nxb2 != nx-1) nxb2r = nxb2+1;
      if (i<nxb2) {
        return x0 + Lxb2*tanh( cs*Scalar(i)/(nxb2) )/tanh( cs );
      }
      else if (i>=nxb2) {
        const Size ii = i-nxb2;
        const Scalar result = x0 + Lxb2 + Lxb2 *
          (1.0 - tanh( cs*Scalar((nxb2r)-ii)/(nxb2r) )/tanh( cs ) );
        return result;
      }
    }
    error("Mesh::distribute illegal options");
    return 0.0;
  }

  /// True if point is in a Line element
  static bool is_in_element_line(const Point &pnode,
                                 const std::vector<Point> &vertex,
                                 const Scalar epsilon);
  /// True if point is in a Tri element
  static bool is_in_element_tri(const Point &pnode,
                                const std::vector<Point> &vertex,
                                const Scalar epsilon);
  /// True if point is in a Tet element
  static bool is_in_element_tet(const Point &pnode,
                                const std::vector<Point> &vertex,
                                const Scalar epsilon);
  /// True if point is in a Quad element
  static bool is_in_element_quad(const Point &pnode,
                                 const std::vector<Point> &vertex,
                                 const Scalar epsilon);
  /// True if point is in a Hex element
  static bool is_in_element_hex(const Point &pnode,
                                const std::vector<Point> &vertex,
                                const Scalar epsilon);

  void CopyIn(ifstream &in, const vector<Element*> &el,
              const Partition<Size,Ordinal,Scalar>::Ptr partition);
  void CopyIn(const vector<Element*> &el);
  //@}
};

//============================================================================
//                      I m p l e m e n t a t i o n
//============================================================================

  /// Output Mesh to a file stream
  ostream & operator<<(ostream &os, const Mesh &mesh) {
    os << "Mesh Output" << endl;
    os << "  ne = " << mesh.ne << endl;
    os << "  nsd = " << mesh.nsd << endl;
    os << "  numPoints = " << mesh.numPoints();
    return os;
  }

} // namespace DGM

#endif  // DGM_MESH_HPP
