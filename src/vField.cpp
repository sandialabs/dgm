/** \file vField.cpp
    \brief Vector of DGM Field container implementation
    \author Scott Collis
    \copyright (c)2014 Sandia National Laboratories
*/

// system includes
#include <memory>
#include <cstdio>
#include <fstream>
#include <ostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctime>
#include <inttypes.h>
using namespace std;

// boost includes
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
using boost::lexical_cast;
using boost::numeric_cast;
#include <boost/filesystem.hpp>

// Blosc includes (used for data compression)
#ifdef DGM_DEBUG_BLOSC
#include "blosc.h"
#endif

// DGM includes
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#endif
#include "Field.hpp"
#include "String.hpp"
#include "vField.hpp"
#include "vField.tpp"
#include "ParUtils.hpp"
#include "Partition.tpp"

// Trilinos includes
#ifdef DGM_USE_EPETRA
#ifdef DGM_PARALLEL
#include "Epetra_MpiComm.h"
#else
#include "Epetra_SerialComm.h"
#endif
#include "Epetra_Map.h"
#include "Epetra_BlockMap.h"
#include "Epetra_Vector.h"
#include "Epetra_Export.h"
#include "Epetra_Import.h"
#include "Epetra_CombineMode.h"
#endif

namespace DGM {

/// Default constructor
vField::vField(const DGM::Comm::Ptr comm_, string i_name) :
  comm(comm_), sigma(0.0), name(i_name), contiguous(false),
  use_epetra(true), partition() {
  if (comm->verbosity()>2)
    comm->cout() << "Default vField() constructor" << endl;
}

/// Copy constructor
vField::vField(const vField &G) :
  F(G.F), comm(G.comm), sigma(G.sigma), name(G.name),
  contiguous(G.contiguous), use_epetra(true), partition(G.partition) {
  if (comm->verbosity()>4) comm->cout() << "vField(const vField &) for "
                                        << name << endl;
}

/// Destructor
vField::~vField() {
  // no need to output if the vField was never allocated or named
  if ((comm->verbosity() && name=="vField") && size() != 0)
    comm->cout()<<"~DGM::vField() <unnamed>"<<endl;
  else if (comm->verbosity())
    comm->cout()<<"~DGM::vField() "<<name<<endl;
}

/// Reset the vField interior and side storage to be contiguous
/** \warning This really should release the Field storage first. */
void vField::reset_storage() {
  if(comm->verbosity()>3)
    comm->cout() << "vField::reset_storage on vField " << name
                 << " with\n  qtot = " << qtot()
                 << " and sdof = " << sdof() <<endl;
  if (size()==0) {
    comm->cout() << "\nWARNING - vField::reset_storage on vField " << name
                 << " is of zero size! Returning with an no-op." <<endl;
    return;
  }
  // Note that qtot() and sdof() will throw if they exceed LocalSize
  elmt_data.resize(qtot());
  side_data.resize(sdof());
  elmt_data = 0;
  side_data = 0;
  LocalSize eid=0, sid=0;
  for (vField::size_type i=0; i<size(); i++) {
    dVector eld, sld;
    eld.alias(elmt_data, eid, F[i]->qtot());
    eid += F[i]->qtot();
    sld.alias(side_data, sid, F[i]->sdof());
    sid += F[i]->sdof();
    F[i]->reset_storage(eld, sld);
  }
  contiguous=true;
  if (use_epetra) setup_epetra();
#ifdef DGM_PARALLEL
  // make partition contiguous
  pcbuf.resize(partition->ncprocs());
  pcsbuf.resize(partition->ncprocs());
  iVector len(partition->ncprocs());
  len=0;
  for (LocalSize n=0; n<partition->ncprocs(); n++) {
    for (vField::size_type i=0; i<size(); i++) len[n] += F[i]->pc[n]->len;
    pcbuf[n].resize(len[n]);
    pcsbuf[n].resize(len[n]);
    // reset pc storage
    LocalSize start=0;
    for (vField::size_type i=0; i<size(); i++) {
      F[i]->pc[n]->buf.alias( pcbuf[n], start, F[i]->pc[n]->len );
      F[i]->pc[n]->sbuf.alias( pcsbuf[n], start, F[i]->pc[n]->len );
      start += F[i]->pc[n]->len;
      // now reset side storage
      LocalSize pcstart=0;
      for (size_t j=0; j<F[i]->pc[n]->side.size(); j++) {
        F[i]->pc[n]->side[j]->u.alias( F[i]->pc[n]->buf, pcstart,
                                       F[i]->pc[n]->side[j]->qtot() );
        pcstart += F[i]->pc[n]->side[j]->qtot();
      }
    }
  }
#endif
}

/// Share each Field's sides across a DGM::Comm using nonblocking communication
/** If the vField storage is contiguous, then all the Field side data is
    transfered in one communication call.  If it is not contiguous, then
    each Field in the vField issues its own communication calls. */
void vField::begin_share_sides() {
  // static bool first_time(true);
#ifdef DGM_PARALLEL
  if (!contiguous) {
    for (vField::size_type i=0; i<size(); i++) F[i]->begin_share_sides();
  } else {
    //if (first_time) {
    //  comm->cout()<<"Using vField::begin_share_sides()"<<endl;
    //  first_time=false;
    //}
    // receive side information from neighbors directly to partition buffer
    for (LocalSize n=0; n<partition->ncprocs(); n++) {
      comm->iReceive( comm->MyPID(), pcbuf[n].data(),
                      pcbuf[n].size(), partition->cinfo[n].cprocid );
    }
    // Fill send buffer and send side information to neighbors
    for (LocalSize n=0; n<partition->ncprocs(); n++) {
      for (vField::size_type i=0; i<size(); i++) {
        Ordinal sdof = 0;
        for (Ordinal j=0; j<F[i]->partition->cinfo[n].nsides; j++) {
          const GlobalSize elmtid = F[i]->partition->cinfo[n].links[j].elmtid;
          const LocalSize sideid = F[i]->partition->cinfo[n].links[j].sideid;
          const GlobalSize sidegid = partition->cinfo[n].links[j].sidegid;
          const Side *s=F[i]->el[elmtid]->side[sideid];
          if (s->subsides().empty()) {
            for (LocalSize q=0; q<s->qtot(); q++)
              F[i]->pc[n]->sbuf[sdof++] = s->u[q];
          } else {
            for (size_t k=0; k<s->subsides().size(); ++k) {
              const Side::Ptr ss = s->subsides()[k];
              if (ss->gid() == sidegid) {
                for (LocalSize q=0; q<ss->qtot(); q++)
                  F[i]->pc[n]->sbuf[sdof++] = ss->u[q];
                break;
              }
            }
          }
        }
      }
      comm->iSend( partition->cinfo[n].cprocid, pcsbuf[n].data(),
                   pcsbuf[n].size(), partition->cinfo[n].cprocid );
    }
  }
#endif
}

/// Share each Field's sides across a DGM::Comm
void vField::end_share_sides() const {
#ifdef DGM_PARALLEL
  if (!contiguous)
    for (vField::size_type i=0; i<size(); i++) F[i]->end_share_sides();
  else
    comm->WaitAll();
#endif
}

/// Setup Epetra datastructures
void vField::setup_epetra() {
#ifdef DGM_USE_EPETRA
  const int verb = comm->verbosity();
  if (verb>2) comm->cout() << "vField::setup_epetra for vField = "<<name<<endl;
#ifdef DGM_PARALLEL
  eComm.reset( new Epetra_MpiComm((dynamic_cast<const DGM::MpiComm*>
                                   (comm.get())->mpicomm())) );
  // see if too many dofs to use Epetra which requires int32
  {
  Ordinal Lmax=0;
  comm->MaxAll(&F[0]->Lmax,&Lmax,1);
  if (verb>2)
    comm->cout()<<"  Lmax = "<<Lmax<<", size() = "<<size()<<", gne = "
                <<F[0]->partition->gne()<<endl;
  const uint64_t numDOF = numeric_cast<uint64_t>(Lmax) *
                          numeric_cast<uint64_t>(size()) *
                          numeric_cast<uint64_t>(F[0]->partition->gne());
  if (verb>2) comm->cout()<<"  numDOF = "<<numDOF<<endl;
  if ( numeric_cast<uint64_t>(numeric_limits<int>::max()) <= numDOF ) {
    use_epetra = false;
    // Epetra_BlockMap not 64 bit clean
    comm->cout()<<"  WARNING: not using Epetra_BlockMap, problem too large\n"
                  "           to fit in int32 index type."<<endl;
    return;
  }
  }
  // make datastructure for Epetra nodal and modal maps
  int ne(0), loc(0);
  // compute total number of my elements
  for (vField::size_type i=0; i<size(); i++) ne += F[i]->partition->ne();
  // comm->cout()<<"  Total vField ne = "<<ne<<endl;
  iVector eid(ne), nodal_len(ne), modal_len(ne);
  for (Ordinal k=0; k<F[0]->partition->ne(); k++, loc++) {
    eid[loc] = F[0]->partition->eid(k);
    modal_len[loc] = F[0]->partition->len[k];
    nodal_len[loc] = F[0]->partition->nodal_len[k];
  }
  //cout << comm->MyPID() << ": ne = " << F[0]->partition->ne() << endl;
  //cout << "global_ne = " << F[0]->partition->part.size() << endl;
  int offset = numeric_cast<int>(F[0]->partition->gne());
  for (vField::size_type i=1; i<size(); i++) {
    for (Ordinal k=0; k<F[i]->partition->ne(); k++, loc++) {
      eid[loc] = offset + F[i]->partition->eid(k);
      modal_len[loc] = F[i]->partition->len[k];
      nodal_len[loc] = F[i]->partition->nodal_len[k];
    }
    offset += F[i]->partition->gne();
  }
  // see if too many dofs to use Epetra which requires int32
  const uint64_t max_len=ne?*max_element(modal_len.begin(), modal_len.end()):0;
  const uint64_t numDOF = max_len * numeric_cast<uint64_t>(size()) *
                          numeric_cast<uint64_t>(F[0]->partition->gne());
  if ( numeric_cast<uint64_t>(INT_MAX) <= numDOF ) {
    // Epetra_BlockMap not 64 bit clean
    use_epetra = false;
    comm->cout()<<"  WARNING: not using Epetra_BlockMap, "
                  "problem too large."<<endl;
    return;
  }
  //if (comm->MyPID()==1) cout << eid << endl;
  try {
    const std::vector<int> EID(eid.begin(), eid.end());
    const std::vector<int> MOD(modal_len.begin(), modal_len.end());
    const std::vector<int> NOD(nodal_len.begin(), nodal_len.end());
    modal_map.reset( new Epetra_BlockMap( -1, ne, EID.data(), MOD.data(),
                                           0, *eComm ) );
    nodal_map.reset( new Epetra_BlockMap( -1, ne, EID.data(), NOD.data(),
                                           0, *eComm ) );
  } catch (int Error) {
    if (Error == -1) comm->error("Illegal NumGlobalElements");
    if (Error == -2) comm->error("NumMyElements < 0");
    if (Error == -3) comm->error("ElementSize <= 0");
    if (Error == -4) comm->error("Invalid NumGlobalElements");
    if (Error == -5)
      comm->error("Minimum global element index is less than index base");
    if (Error == -9) comm->error("Internal Epetra_BlockMap error");
  }
  if (verb>3) {
    comm->cout()<<"  modal_map->NumGlobalElements() = "
                <<modal_map->NumGlobalElements()<<endl;
    comm->cout()<<"  modal_map->NumMyElements() = "
                <<modal_map->NumMyElements()<<endl;
    comm->cout()<<"  nodal_map->NumGlobalElements() = "
                <<nodal_map->NumGlobalElements()<<endl;
    comm->cout()<<"  nodal_map->NumMyElements() = "
                <<nodal_map->NumMyElements()<<endl;
  }
#else  // !DGM_PARALLEL
  eComm.reset( new Epetra_SerialComm );
  //cout << "nmodes = " << nmodes() << " qtot = " << qtot() << endl;
#if 0
  // point maps don't work for building sparse matrix
  modal_map.reset( new Epetra_Map( -1, nmodes(), 0, *eComm ) );
  nodal_map.reset( new Epetra_Map( -1, qtot(), 0, *eComm ) );
#else
  int ne(0), loc(0), offset(0);
  for (size_type i=0; i<size(); i++) ne += F[i]->ne;
  iVector eid(ne), nodal_len(ne), modal_len(ne);
  for (size_type i=0; i<size(); i++) {
    for (LocalSize k=0; k<F[i]->ne; k++, loc++) {
      eid[loc] = offset + k;
      modal_len[loc] = F[i]->el[k]->nModes();
      nodal_len[loc] = F[i]->el[k]->qtot;
    }
    offset += F[i]->ne;
  }
  modal_map.reset( new Epetra_BlockMap( -1, ne,
    reinterpret_cast<int*>(eid.data()),
    reinterpret_cast<int*>(modal_len.data()), 0, *eComm ) );
  nodal_map.reset( new Epetra_BlockMap( -1, ne,
    reinterpret_cast<int*>(eid.data()),
    reinterpret_cast<int*>(nodal_len.data()), 0, *eComm ) );
#endif
#endif  // DGM_PARALLEL

  modal_vec.reset(new Epetra_Vector(View, *modal_map, elmt_data.data()));
  nodal_vec.reset(new Epetra_Vector(View, *nodal_map, elmt_data.data()));

  // make a point map and view
  nodal_pnt_map = BlockMap2PointMap(*nodal_map.get());
  nodal_pnt_vec.reset(new Epetra_Vector(View, *nodal_pnt_map,
                                        elmt_data.data()));

  rdofmap = BlockMap2PointMap(*modal_map.get());

  // DG map
  rdof_per_ele.clear();
  int ildof = 0;
  for (size_t ifield = 0; ifield < F.size(); ++ifield) {
    for (LocalSize e = 0; e < F[ifield]->ne; ++e) {
      Element *const ele = F[ifield]->el[e];
      const int nmodes = ele->nModes();
      if (ifield == 0) {
        rdof_per_ele[ele->gid()] = vector<int>(0);
        rdof_per_ele[ele->gid()].reserve(nmodes*F.size()); // <- just a guess
      }
      vector< vector<int> > &fielddofs = dof_per_fieldele[ele->gid()];
      if (fielddofs.empty()) {
        fielddofs.resize(F.size());
      }
      for (int imode = 0; imode < nmodes; ++imode) {
        const int dofGID = RowDofMapPtr()->GID(ildof);
        assert(dofGID >= 0);
        rdof_per_ele[ele->gid()].push_back(dofGID);
        fielddofs[ifield].push_back(dofGID);
        ildof++;
      }
    }
  }
#endif  // DGM_USE_EPETRA
}

//============================================================================
//                         v F i e l d   I O
//============================================================================

namespace {

/// Implementation for serial read supporting different data types
template <typename fileGlobal, typename fileLocal, typename fileScalar>
streamoff serial_read(vector<Field::Ptr> &vF,
                      const string &fname,
                      const streamoff offset,
                      const DGM::Comm::Ptr comm) {
  typedef DGM::Ordinal myLocal;
  //typedef DGM::Size myGlobal;
  typedef DGM::Scalar myScalar;
  const fileScalar quiet_NaN = std::numeric_limits<fileScalar>::quiet_NaN();
  ifstream fs(fname.c_str(), ifstream::binary);
  fs.seekg(offset); // position file pointer at offset
#ifdef DGM_FIELD_TRANSFORM
  // read in transform space
  for (size_t f=0; f<vF.size(); f++) {
    Field::Ptr F = vF[f];
    if (fs.eof()) {
      cout<<"Error: vField::read file is at EOF: "<<fname<<endl;
      comm->error("Error in vField::typename, "
                  "file cannot be at EOF but it is", 1);
      return 0;
    }
    else if (!fs.good()) {
      cout<<"Error: file "<<fname<<" is not good, i = "<<f<<endl;
      comm->error("Error in vField::serial_read, file state is not good", 1);
      return 0;
    }
    fileGlobal glen;
    CMC::Vector<fileLocal, myLocal> L(F->ne);
    CMC::Vector<fileGlobal, myLocal> D(F->ne);
    const streamsize L_size=numeric_cast<streamsize>(F->ne*sizeof(fileLocal));
    const streamsize D_size=numeric_cast<streamsize>(F->ne*sizeof(fileGlobal));
    // read global data length, element data lengths, element displacements
    fs.read(reinterpret_cast<char*>(&(glen)),sizeof(fileGlobal));
    fs.read(reinterpret_cast<char*>(L.data()),L_size);
    fs.read(reinterpret_cast<char*>(D.data()),D_size);
    // read the data
    for (myLocal e=0; e<F->ne; e++) {
      const myLocal l = numeric_cast<myLocal>(L[e]);
      CMC::Vector<fileScalar, myLocal> tmp(l, quiet_NaN);
      CMC::Vector<myScalar, myLocal> FtoM(l);
      const streamsize E_size = numeric_cast<streamsize>(l*sizeof(fileScalar));
      fs.read(reinterpret_cast<char*>(tmp.data()),E_size);
      for (myLocal i=0; i<l; ++i) FtoM[i] = numeric_cast<myScalar>(tmp[i]);
      F->el[e]->zero();
      F->el[e]->set(FtoM,l);
    }
  }
#ifdef DGM_VFIELD_EOF_TEST
  // trigger eof read.  SSC:  This could break other things?
  int eof;
  fs >> eof;
  if (!fs.eof()) {
    cout<<"Error: vField::read file not at EOF: "<<fname<<endl;
    cout<<"  tellg() = "<<fs.tellg()<<endl;
    cout<<"  number of unformatted reads = "<<size<<endl;
    comm->error("Error in vField::read expected end of file and it's not.");
    return 0;
  }
#endif
#else
  // read in physical space
  if (typeid(fileScalar) == typeid(myScalar)) {
    for (size_t f=0; f<vF.size(); f++) {
      Field::Ptr F = vF[f];
      const myLocal N = F->elmt_data.size();
      const streamsize size = numeric_cast<streamsize>(sizeof(fileScalar)*N);
      fs.read(reinterpret_cast<char*>(F->elmt_data.data()), size);
    }
  } else {
    for (size_t f=0; f<vF.size(); f++) {
      Field::Ptr F = vF[f];
      const myLocal N = F->elmt_data.size();
      CMC::Vector<fileScalar, myLocal> tmp(N, quiet_NaN);
      const streamsize size = numeric_cast<streamsize>(sizeof(fileScalar)*N);
      fs.read(reinterpret_cast<char*>(tmp.data()), size);
      for (myLocal j=0; j<N; ++j)
        F->elmt_data[j] = numeric_cast<myScalar>(tmp[j]);
    }
  }
#endif
  return fs.tellg();
}

/// Implementation of file read with compression support
template <typename fileGlobal, typename fileLocal, typename fileScalar>
streamoff compressed_serial_read(vector<Field::Ptr> &vF,
                                 const string &fname,
                                 const streamoff offset,
                                 const DGM::Comm::Ptr comm) {
  typedef DGM::Ordinal myLocal;
  //typedef DGM::Size myGlobal;
  typedef DGM::Scalar myScalar;
  const fileScalar quiet_NaN = std::numeric_limits<fileScalar>::quiet_NaN();
#ifdef DGM_DEBUG_BLOSC
  blosc_init();
  const string compressor = "lz4hc";
  const int comp = blosc_set_compressor(compressor.c_str());
  if (comp<0) comm->error("Could not set compression scheme: "+compressor);
#endif
  ifstream fs(fname.c_str(), ifstream::binary);
  fs.seekg(offset); // position file pointer at offset
#ifdef DGM_FIELD_TRANSFORM
  // read in transform space
  for (size_t n=0; n<vF.size(); n++) {
    //comm->cout()<<"Working on Field["<<n<<"] = "<<vF[n]->name<<endl;
    Field::Ptr F = vF[n];
    if (fs.eof()) {
      cout<<"Error: vField::read file is at EOF: "<<fname<<endl;
      comm->error("Error in vField::typename, "
                  "file cannot be at EOF but it is");
      return 0;
    } else if (!fs.good()) {
      cout<<"Error: file "<<fname<<" is not good, i = "<<n<<endl;
      comm->error("Error in vField::serial_read, file state is not good");
      return 0;
    }
    fileGlobal glen;
    CMC::Vector<fileLocal, myLocal> L(F->ne);
    CMC::Vector<fileGlobal, myLocal> D(F->ne);
    const streamsize L_size=numeric_cast<streamsize>(F->ne*sizeof(fileLocal));
    const streamsize D_size=numeric_cast<streamsize>(F->ne*sizeof(fileGlobal));
    // read global data length, element data lengths, element displacements
    fs.read(reinterpret_cast<char*>(&(glen)),sizeof(fileGlobal));
    fs.read(reinterpret_cast<char*>(L.data()),L_size);
    fs.read(reinterpret_cast<char*>(D.data()),D_size);
#ifdef DGM_DEBUG_BLOSC
    // Read the data (compressed)
    static bool firstwarn=true;
    if (firstwarn) {
      line(comm->cout());
      comm->cout()<<"WARNING:  BLOSC decompressor ("<<compressor
                  <<") is experimental"<<endl;
      line(comm->cout());
      firstwarn = false;
    }
    fileLocal csize = 0;
    char *c_size = reinterpret_cast<char*>(&csize);
    fs.read(c_size,sizeof(csize));
    //comm->cout()<<"Field: "<<F->name<<", csize = "<<csize<<endl;
    std::vector<char> ctmp(csize);
    //const streamoff start = fs.tellg();
    fs.read(reinterpret_cast<char*>(&(ctmp[0])),csize);
    //comm->cout()<<"Read Field "<<F->name<<" at "<<start<<" to "
    //            <<fs.tellg()<<endl;
    const myLocal ndof = F->ndof();
    myLocal dsize = ndof*sizeof(fileScalar);
    CMC::Vector<fileScalar, myLocal> tmp(ndof, quiet_NaN);
    dsize = blosc_decompress(&(ctmp[0]),tmp.data(),dsize);
#ifdef DGM_VERBOSE_COMPRESSION
    comm->cout()<<"Decompressing "<<F->name<<": "<<dsize<<" <- "<<csize<<" ("
                <<(1.*dsize)/csize<<"x)"<<endl;
#endif
    assert(dsize==ndof*sizeof(fileScalar));
    for (myLocal e=0, k=0; e<F->ne; e++) {
      const myLocal l = numeric_cast<myLocal>(L[e]);
      CMC::Vector<myScalar, myLocal> FtoM(l);
      for (myLocal i=0; i<l; ++i, ++k) FtoM[i]=numeric_cast<myScalar>(tmp[k]);
      F->el[e]->zero();
      F->el[e]->set(FtoM,l);
    }
#else
    // read the data (uncompressed)
    for (myLocal e=0; e<F->ne; e++) {
      const myLocal l = numeric_cast<myLocal>(L[e]);
      CMC::Vector<fileScalar, myLocal> tmp(l, quiet_NaN);
      CMC::Vector<myScalar, myLocal> FtoM(l);
      const streamsize E_size = numeric_cast<streamsize>(l*sizeof(fileScalar));
      fs.read(reinterpret_cast<char*>(tmp.data()),E_size);
      for (myLocal i=0; i<l; ++i) FtoM[i] = numeric_cast<myScalar>(tmp[i]);
      F->el[e]->zero();
      F->el[e]->set(FtoM,l);
    }
#endif
  }
#else
  // read in physical space
  if (typeid(fileScalar) == typeid(myScalar)) {
    for (size_t n=0; n<vF.size(); n++) {
      Field::Ptr F = vF[n];
      const myLocal N = F->elmt_data.size();
      const streamsize size = numeric_cast<streamsize>(sizeof(fileScalar)*N);
      fs.read(reinterpret_cast<char*>(F->elmt_data.data()), size);
    }
  } else {
    for (size_t n=0; n<vF.size(); n++) {
      Field::Ptr F = vF[n];
      const myLocal N = F->elmt_data.size();
      CMC::Vector<fileScalar, myLocal> tmp(N, quiet_NaN);
      const streamsize size = numeric_cast<streamsize>(sizeof(fileScalar)*N);
      fs.read(reinterpret_cast<char*>(tmp.data()), size);
      for (myLocal j=0; j<N; ++j)
        F->elmt_data[j] = numeric_cast<myScalar>(tmp[j]);
    }
  }
#endif
#ifdef DGM_DEBUG_BLOSC
  blosc_destroy();
#endif
  return fs.tellg();
}

//============================================================================
//                              M P I - I O
//============================================================================
//
// The MPI_read and MPI_write methods use MPI-IO as part of the MPI-2 API
// to efficiently write single image files on parallel systems.
//

#ifdef DGM_PARALLEL

/// Helper for MPI-IO
template <typename fileGlobal, typename fileLocal, typename fileScalar>
MPI_Offset MPI_read(vector<Field::Ptr> &vF,
                    const Partition<Size,Ordinal,Scalar>::Ptr &partition,
                    const string &fname,
                    const MPI_Offset skip,
                    const DGM::Comm::Ptr comm) {

  typedef DGM::Ordinal myLocal;
  typedef DGM::Size    myGlobal;
  typedef DGM::Scalar  myScalar;

  if(comm->verbosity()>4) comm->cout()<<"vField::MPI_read("<<fname<<")"<<endl;
  const char *cnative="native";
  char *native = const_cast<char*>(cnative);

  MPI_File fh;
  MPI_Status status;
  MPI_Datatype scalar_type, local_type, global_type;
  MPI_Offset disp = skip; // absolute offset in bytes from the beginning

  const myLocal NE = partition->ne();
  MPI_Info info;
  MPI_Info_create(&info);
#ifdef DGM_MPI_IO_HINTS
  // Try out the ROMIO Info "hints"
  MPI_Info_set(info,"cb_nodes","1");
#endif
  {
    std::vector<int> ilen(NE,1);
    std::vector<MPI_Aint> idisp(NE);
    for (myLocal i=0; i<NE; ++i)
      idisp[i]= numeric_cast<MPI_Aint>(partition->eid(i)*sizeof(fileLocal));
    if (const int stat = MPI_Type_create_hindexed(NE, &ilen.front(),
                                                  &idisp.front(),
                                                  mpiType<fileLocal>(),
                                                  &local_type))
      comm->error("2: MPI_Type_hindexed", stat);
    if (const int stat = MPI_Type_commit( &local_type ))
      comm->error("2: MPI_Type_commit",stat);
  }
  {
    std::vector<int> ilen(NE,1);
    std::vector<MPI_Aint> idisp(NE);
    for (myLocal i=0; i<NE; ++i)
      idisp[i]= numeric_cast<MPI_Aint>(partition->eid(i)*sizeof(fileGlobal));
    if (const int stat = MPI_Type_create_hindexed(NE, &ilen.front(),
                                                  &idisp.front(),
                                                  mpiType<fileGlobal>(),
                                                  &global_type))
      comm->error("2.1: MPI_Type_hindexed", stat);
    if (const int stat = MPI_Type_commit( &global_type ))
      comm->error("2.1: MPI_Type_commit",stat);
  }

  string nname = fname;

  MPI_Comm mpicomm = dynamic_cast<const DGM::MpiComm*>(comm.get())->mpi_comm;

#if 0
  // this open mode does not work on Win2000 for some odd reason
  if (int stat = MPI_File_open(mpicomm,const_cast<char *>(nname.c_str()),
                               MPI_MODE_RDONLY, info, &fh))
    comm->error("MPI_File_open", stat);
#else
  if (int stat = MPI_File_open(mpicomm,const_cast<char *>(nname.c_str()),
                               MPI_MODE_RDWR | MPI_MODE_CREATE,
                               info, &fh)) {
    stringstream msg;
    msg << "MPI_File_open failed to open file " << nname
        << " with return status = " << stat;
    throw exception(msg.str());
  }
#endif

#ifdef DGM_FIELD_TRANSFORM
  // read each Field in transform space (use collective IO for efficiency)
  fileGlobal glen;
  CMC::Vector<fileLocal,  myLocal> L(NE);
  CMC::Vector<fileGlobal, myLocal> D(NE);
  for (size_t f=0; f<vF.size(); f++) {
    Field::Ptr F = vF[f];

    if (const int stat = MPI_File_set_view(fh, disp, mpiType<fileGlobal>(),
                                           mpiType<fileGlobal>(),
                                           native, info) )
      comm->error("1: MPI_File_set_view", stat);
    if (const int stat = MPI_File_read_all(fh, &glen, 1,
                                           mpiType<fileGlobal>(), &status))
      comm->error("1: MPI_File_read_all",stat);
    disp += sizeof(fileGlobal);

    // read partition data lengths
    if (const int stat = MPI_File_set_view(fh, disp, mpiType<fileLocal>(),
                                           local_type, native, info) )
      comm->error("2: MPI_File_set_view", stat);
    if (const int stat = MPI_File_read_all(fh, L.data(), NE,
                                           mpiType<fileLocal>(), &status))
      comm->error("2: MPI_File_read_all",stat);
    disp += partition->gne()*sizeof(fileLocal);

    // get partition data displacements
    if (const int stat = MPI_File_set_view(fh, disp, mpiType<fileGlobal>(),
                                           global_type, native, info) )
      comm->error("3: MPI_File_set_view", stat);
    if (int stat = MPI_File_read_all(fh, D.data(), NE, mpiType<fileGlobal>(),
                                     &status))
      comm->error("3: MPI_File_read_all",stat);
    disp += partition->gne()*sizeof(fileGlobal);

    myLocal T_len=0;
    {
      std::vector<int> ilen(NE);
      std::vector<MPI_Aint> idisp(NE);
      for (myLocal i=0; i<NE; ++i) {
        ilen[i]  = numeric_cast<int>(L[i]);
        T_len   += numeric_cast<int>(L[i]);
        idisp[i] = numeric_cast<MPI_Aint>(D[i])*sizeof(fileScalar);
      }
      if (const int stat = MPI_Type_create_hindexed(NE,&ilen.front(),
                                                    &idisp.front(),
                                                    mpiType<fileScalar>(),
                                                    &scalar_type) )
        comm->error("1: MPI_Type_hindexed ", stat);
      if (const int stat = MPI_Type_commit( &scalar_type ) )
        comm->error("1: MPI_Type_commit ", stat);
    }
    if (const int stat = MPI_File_set_view(fh, disp,  mpiType<fileScalar>(),
                                           scalar_type, native, info))
      comm->error("4: MPI_File_set_view", stat);

    CMC::Vector<myScalar, myLocal> FtoM(T_len);
    {
      CMC::Vector<fileScalar, myLocal> T(T_len);
      const int T_mpi  = numeric_cast<int>(T_len);
      if (const int stat = MPI_File_read_all(fh, T.data(), T_mpi,
                                             mpiType<fileScalar>(), &status))
        comm->error("4: MPI_File_read_all",stat);
      disp += glen*sizeof(fileScalar);

      for (myLocal i=0; i<T_len; ++i) FtoM[i] = numeric_cast<myScalar>(T[i]);
    }

    if (const int stat = MPI_Type_free( &scalar_type ))
      comm->error("4: MPI_Type_free",stat);

    // put in element storage
    myGlobal cnt = 0;
    CMC::Vector<myScalar, myLocal> Tmp;
    for (myLocal e=0; e<F->ne; e++) {
      F->el[e]->zero();
      Tmp.alias(FtoM, cnt, L[e]);
      F->el[e]->set(Tmp,L[e]);
      cnt += L[e];
    }
  }
#else
  // Build my proceses scalar_type for data using MPI_Type_create_hindexed
  {
    std::vector<int> ilen(NE);
    std::vector<MPI_Aint> idisp(NE);
    for (myLocal j=0; j<NE; ++j) {
      ilen[j]  = numeric_cast<int>(partition->len[j]);
      idisp[j] = numeric_cast<MPI_Aint>(partition->disp[j]*sizeof(fileScalar));
    }
    if (const int stat =
        MPI_Type_create_hindexed(NE, &ilen.front(),
                                 &idisp.front(), mpiType<fileScalar>(),
                                 &scalar_type))
      comm->error("7: MPI_Type_hindexed ", stat);
  }
  if (const int stat = MPI_Type_commit( &scalar_type ))
    comm->error("8: MPI_Type_commit ", stat);

  // read each Field in physical space (use collective IO for efficiency)
  for (size_t f=0; f<vF.size(); f++) {
    Field::Ptr F = vF[f];
    const myLocal T_len = numeric_cast<myLocal>(F->elmt_data.size());
    const int T_mpi = numeric_cast<int>(T_len);
    CMC::Vector<fileScalar, myLocal> T(T_len);
    if (const int stat = MPI_File_set_view(fh, disp, mpiType<fileScalar>(),
                                           scalar_type, native, info))
      comm->error("8: MPI_File_set_view ", stat);
    if (const int stat = MPI_File_read_all(fh, T.data(), T_mpi,
                                           mpiType<fileScalar>(), &status))
      comm->error("8: MPI_File_read_all ", stat);

    disp += partition->glen()*sizeof(fileScalar);  // must be in bytes
    for (myLocal i=0; i<T_len; ++i)
      F->elmt_data[i] = numeric_cast<myScalar>(T[i]);
  }
  MPI_Type_free( &scalar_type );
#endif
  if (int stat = MPI_Type_free( &local_type ))
    comm->error("5: MPI_Type_free",stat);
  if (int stat = MPI_Type_free( &global_type))
    comm->error("6: MPI_Type_free",stat);
  if (int stat = MPI_File_close(&fh))
    comm->error("5: MPI_File_close",stat);
  MPI_Info_free(&info);
  if (comm->verbosity()>4)
    comm->cout() << "vField::read("<<fname<<")"
    << " completed with disp = "<<disp<<endl;
  return disp;
}

/// Helper function for MPI-IO
/** \note The write routine is not templated as we only write in the current
          data types. */
MPI_Offset MPI_write(const vector<Field::Ptr> &vF,
                     const Partition<Size,Ordinal,Scalar>::Ptr &partition,
                     const string &fname,
                     const MPI_Offset skip,
                     const DGM::Comm::Ptr comm) {
  if (comm->verbosity()>4)
    comm->cout() << "vField::MPI_write("<<fname<<")"<< endl;

  typedef vField::LocalSize LocalSize;
  typedef vField::GlobalSize GlobalSize;

  char native[] = "native";
  MPI_File fh;
  MPI_Status status;
  MPI_Datatype scalar_type, local_type, global_type;
  MPI_Offset disp = skip;  // absolute offset in bytes from the beginning

  // Try out the ROMIO Info "hints"
  MPI_Info info;
  MPI_Info_create(&info);
#ifdef DGM_MPI_IO_HINTS
  MPI_Info_set(info, "cb_nodes","1");
  MPI_Info_set(info, "romio_no_indep_rw","true");
#endif

  // Build my processes data-types using MPI_Type_hindexed
  {
    const LocalSize nl = partition->len.size();
    const LocalSize nd = partition->disp.size();
    const LocalSize ne = partition->ne();
    std::vector<int> ilen(nl);
    std::vector<MPI_Aint> idisp(nd);
    const LocalSize pos_ne = std::max(ne,numeric_cast<LocalSize>(1));
    for (LocalSize i=0; i<nl; ++i)
      ilen[i] = numeric_cast<int>(partition->len[i]);
    for (LocalSize i=0; i<nd; ++i)
      idisp[i] = numeric_cast<MPI_Aint>(partition->disp[i])*sizeof(Scalar);
    int idummy_address=0;
    MPI_Aint adummy_address=0;
    int      * ilen_data  =  ilen.empty() ? &idummy_address :  &ilen.front();
    MPI_Aint * idisp_data = idisp.empty() ? &adummy_address : &idisp.front();
    if (const int stat = MPI_Type_create_hindexed(pos_ne,
                                                  ilen_data,
                                                  idisp_data,
                                                  mpiType<Scalar>(),
                                                  &scalar_type) )
      comm->error("1: MPI_Type_hindexed ", stat);
    if (const int stat = MPI_Type_commit( &scalar_type ) )
      comm->error("1: MPI_Type_commit ", stat);
  }
  {
    const LocalSize ne = partition->ne();
    std::vector<int> ilen(ne,1);
    std::vector<MPI_Aint> idisp(ne);
    for (LocalSize i=0; i<ne; ++i)
      idisp[i]= numeric_cast<MPI_Aint>(partition->eid(i)*sizeof(LocalSize));
    const LocalSize pos_ne = std::max(ne,numeric_cast<LocalSize>(1));
    int idummy_address=0;
    MPI_Aint adummy_address=0;
    int      * ilen_data  =  ilen.empty() ? &idummy_address :  &ilen.front();
    MPI_Aint * idisp_data = idisp.empty() ? &adummy_address : &idisp.front();
    if (const int stat = MPI_Type_create_hindexed(pos_ne, ilen_data,
                                                  idisp_data,
                                                  mpiType<LocalSize>(),
                                                  &local_type))
      comm->error("2: MPI_Type_hindexed", stat);
    if (const int stat = MPI_Type_commit( &local_type ))
      comm->error("2: MPI_Type_commit",stat);
  }
  {
    const LocalSize ne = partition->ne();
    const LocalSize pos_ne = std::max(ne,numeric_cast<LocalSize>(1));
    std::vector<int> ilen(ne,1);
    std::vector<MPI_Aint> idisp(ne);
    for (LocalSize i=0; i<ne; ++i)
      idisp[i]= numeric_cast<MPI_Aint>(partition->eid(i)*sizeof(GlobalSize));
    int idummy_address=0;
    MPI_Aint adummy_address=0;
    int      * ilen_data  =  ilen.empty() ? &idummy_address :  &ilen.front();
    MPI_Aint * idisp_data = idisp.empty() ? &adummy_address : &idisp.front();
    if (const int stat = MPI_Type_create_hindexed(pos_ne, ilen_data,
                                                  idisp_data,
                                                  mpiType<GlobalSize>(),
                                                  &global_type))
      comm->error("2.1: MPI_Type_hindexed", stat);
    if (const int stat = MPI_Type_commit( &global_type ))
      comm->error("2.1: MPI_Type_commit",stat);
  }

  string nname = fname;

  MPI_Comm mpicomm = dynamic_cast<const DGM::MpiComm*>(comm.get())->mpi_comm;
#if 1
  // This was the default, Guoquan changed this to see if it fixed a problem
  // on the MEMS cluster.
  // comm->cout()<<"MPI_MODE = "<<(MPI_MODE_WRONLY|MPI_MODE_CREATE)<<endl;
#ifdef DGM_MPI_IO_HINTS
  if (const int stat = MPI_File_open(mpicomm, const_cast<char *>(nname.c_str()),
                                     MPI_MODE_WRONLY | MPI_MODE_CREATE,
                                     info, &fh) ) {
    throw exception(string("MPI_File_open failed to open file " + nname));
  }
#else
  if (const int stat = MPI_File_open(mpicomm,const_cast<char *>(nname.c_str()),
                                     MPI_MODE_WRONLY | MPI_MODE_CREATE,
                                     info, &fh) ) {
    char c[MPI_MAX_ERROR_STRING];
    int i;
    MPI_Error_string(stat,c,&i);
    string s(c,i);
    comm->cout()<<" Error from MPI_File_open on file "<<nname
    <<" : "<<s<<endl;
    comm->error("3: MPI_File_open", stat);
  }
#endif
#else
  if (const int stat = MPI_File_open(mpicomm,const_cast<char *>(nname.c_str()),
                                     MPI_MODE_RDWR | MPI_MODE_CREATE,
                                     info, &fh) ) {
    throw exception(string("MPI_File_open failed to open file " + fname));
  }
#endif

#ifdef DGM_FIELD_TRANSFORM
  // write each Field in transform space (use collective IO for efficiency)
  for (size_t i=0; i<vF.size(); i++) {
    vF[i]->forward_transform();
    vF[i]->pack();

    // write global length
    if (const int stat = MPI_File_set_view(fh, disp, mpiType<GlobalSize>(),
                                           mpiType<GlobalSize>(),
                                           native, info) )
      comm->error("4: MPI_File_set_view", stat);
    GlobalSize glen  = numeric_cast<GlobalSize>(partition->glen());
    if (const int stat =
        MPI_File_write_all(fh, &glen, 1, mpiType<GlobalSize>(), &status))
      comm->error("4: MPI_File_write_all",stat);
    disp += sizeof(GlobalSize);

    // write partition data lengths
    if (const int stat = MPI_File_set_view(fh, disp, mpiType<LocalSize>(),
                                           local_type, native, info) )
      comm->error("5: MPI_File_set_view", stat);
    if (const int stat = MPI_File_write_all(fh, partition->len.data(),
                                            partition->ne(),
                                            mpiType<LocalSize>(), &status)) {
      int resultlen;
      vector<char> str(MPI_MAX_ERROR_STRING,0);
      MPI_Error_string(stat, &str[0], &resultlen);
      comm->cerr() << "MPI_File_write_all error: " << &str[0] << endl;
      comm->error("5: MPI_File_write_all",stat);
    }
    disp += partition->gne()*sizeof(LocalSize);

    {
      LocalSize s=0;
      for (LocalSize j=0; j<partition->ne(); j++) s += partition->len[j];
      if (s != vF[i]->ndof()) comm->error("s != vF[i]->ndof()");
    }

    // write partition data displacements
    if (const int stat = MPI_File_set_view(fh, disp, mpiType<GlobalSize>(),
                                           global_type, native, info) )
      comm->error("6: MPI_File_set_view", stat);
    if (const int stat = MPI_File_write_all(fh, partition->disp.data(),
                                            partition->ne(),
                                            mpiType<GlobalSize>(), &status))
      comm->error("6: MPI_File_write_all",stat);
    disp += partition->gne()*sizeof(GlobalSize);

    // write data
    if (const int stat = MPI_File_set_view(fh, disp, mpiType<Scalar>(),
                                           scalar_type, native, info) )
      comm->error("7: MPI_File_set_view", stat);
    if (const int stat = MPI_File_write_all(fh, vF[i]->elmt_data.data(),
                                            vF[i]->ndof(), mpiType<Scalar>(),
                                            &status))
      comm->error("7: MPI_File_write_all",stat);
    disp += partition->glen()*sizeof(Scalar);  // must be in bytes

    vF[i]->unpack();
    vF[i]->backward_transform();
  }
#else
  // write each Field in physical space (use collective IO for efficiency)
  for (size_t i=0; i<vF.size(); i++) {
    if (const int stat = MPI_File_set_view(fh, disp, mpiType<Scalar>(),
                                           scalar_type, native, info) )
      comm->error("MPI_File_set_view", stat);
    if (const int stat = MPI_File_write_all(fh, vF[i]->elmt_data.data(),
                                            vF[i]->elmt_data.size(),
                                            mpiType<Scalar>(), &status))
      comm->error("MPI_File_write",stat);
    disp += partition->glen()*sizeof(Scalar);
  }
#endif
  if (const int stat=MPI_File_close(&fh))
    comm->error("8; MPI_File_close",stat);
  if (const int stat=MPI_Type_free( &scalar_type ))
    comm->error("9: MPI_Type_free",stat);
  if (const int stat=MPI_Type_free( &local_type  ))
    comm->error("9: MPI_Type_free",stat);
  if (const int stat=MPI_Type_free( &global_type ))
    comm->error("9: MPI_Type_free",stat);
  MPI_Info_free(&info);
  if (comm->verbosity()>4)
    comm->cout() << "vField::MPI_write("<<fname<<")"
                << " completed with disp = "<<disp<<endl;
  return disp;
}

#endif  // DGM_PARALLEL

}  // anonymous namespace for IO helpers

//=============================================================================
//                        Regular I/O routines
//=============================================================================

/// Read a vField using current data types and prescribed offset (default 0)
streamoff vField::read(const string &fname, const streamoff offset) {
  const string &global_size = type<GlobalSize>();
  const string &local_size  = type<LocalSize>();
  const string &scalar_size = type<Scalar>();
  return read(fname, global_size, local_size, scalar_size, offset);
}

/// Templated read that issues either serial or parallel I/O
template <typename fileGlobal, typename fileLocal, typename fileScalar>
streamoff vField::read_impl(const string &fname, const streamoff offset) {
  streamoff disp = 0;
#ifdef DGM_PARALLEL
  const MPI_Offset off =
  MPI_read<fileGlobal,fileLocal,fileScalar>(F,partition,fname,offset,comm);
  disp = numeric_cast<streamoff>(off);
#else
#ifdef DGM_DEBUG_BLOSC
  disp = compressed_serial_read<fileGlobal,fileLocal,fileScalar>(F,fname,
                                                                 offset,comm);
#else
  disp = serial_read<fileGlobal,fileLocal,fileScalar>(F,fname,offset,comm);
#endif
#endif
  return disp;
}

/// Issues the correct read depending on data types
streamoff vField::read(const string &fname,
                       const string &global_size,
                       const string &local_size,
                       const string &scalar_size,
                       const streamoff offset) {
  streamoff disp = 0;
  if      ( global_size == "int32" &&
            local_size  == "int32" &&
            scalar_size == "float64" )
    disp = read_impl<int32_t,int32_t,double>(fname,offset);
  else if ( global_size == "uint32" &&
            local_size  == "uint32" &&
            scalar_size == "float64" )
    disp = read_impl<uint32_t,uint32_t,double>(fname,offset);
  else if ( global_size == "int64" &&
            local_size  == "int32" &&
            scalar_size == "float64" )
    disp = read_impl<int64_t,int32_t,double>(fname,offset);
  else if ( global_size == "int64" &&
            local_size  == "int64" &&
            scalar_size == "float64" )
    disp = read_impl<int64_t,int64_t,double>(fname,offset);
  else if ( global_size == "int32" &&
            local_size  == "int32" &&
            scalar_size == "float32" )
    disp = read_impl<int32_t,int32_t,float>(fname,offset);
  else if ( global_size == "int64" &&
            local_size  == "int32" &&
            scalar_size == "float32" )
    disp = read_impl<int64_t,int32_t,float>(fname,offset);
  else if ( global_size == "int64" &&
            local_size  == "int64" &&
            scalar_size == "float32" )
    disp = read_impl<int64_t,int64_t,float>(fname,offset);
  else if ( global_size == "uint64" &&
            local_size  == "uint64" &&
            scalar_size == "float64" )
    disp = read_impl<uint64_t,uint64_t,double>(fname,offset);
  else if ( global_size == "uint64" &&
            local_size  == "int32" &&
            scalar_size == "float64" )
    disp = read_impl<uint64_t,int32_t,double>(fname,offset);
  else
    throw DGM::exception("Unknown data types in file "+fname);
#ifdef DGM_FIELD_TRANSFORM
  backward_transform();
#endif
  return disp;
}

/// Write a vField from a file (either serial or with MPI-IO)
/** \note This writes out version 0 files. */
streamoff vField::write(const string &fname, const streamoff offset) const {
#ifdef DGM_TEST_BYTE_ORDER
  DGM::ByteOrder byteOrder;
  byteOrder.print(comm->cout());
#endif
#ifdef DGM_PARALLEL
  if (dynamic_cast<const DGM::MpiComm*>(comm.get())) {
    return MPI_write(F,partition,fname,offset,comm);
  }
#endif
#ifdef DGM_DEBUG_BLOSC
  blosc_init();
  const string compressor = "lz4hc";
  const int comp = blosc_set_compressor(compressor.c_str());
  if (comp<0) comm->error("Could not set compression scheme: "+compressor);
#endif
  // is there a reason that I have used append mode in the past?
  ofstream fs(fname.c_str(), ofstream::binary|ios::out|ios::app);
  fs.seekp(offset);
  //ofstream nfs("vfield.dat",ofstream::binary);
#ifdef DGM_FIELD_TRANSFORM
  const_cast<vField*>(this)->forward_transform();
  for (size_type i=0; i<size(); i++) {
    // write global data length, could be very large.
    const GlobalSize glen = F[i]->ndof();
    fs.write(reinterpret_cast<const char*>(&glen),sizeof(GlobalSize));
    // write data lengths
    for (LocalSize e=0; e<F[i]->ne; e++) {
      const LocalSize nModes = F[i]->el[e]->nModes();
      fs.write(reinterpret_cast<const char*>(&nModes),sizeof(LocalSize));
    }
    // write data displacements
    GlobalSize disp = 0;
    for (LocalSize e=0; e<F[i]->ne; e++) {
      fs.write(reinterpret_cast<const char*>(&disp),sizeof(GlobalSize));
      disp += F[i]->el[e]->nModes();
    }
    // write the data
#ifdef DGM_DEBUG_BLOSC
    static bool firstwarn=true;
    if (firstwarn) {
      line(comm->cout());
      comm->cout()<<"WARNING:  BLOSC compressor ("<<compressor
                  <<") is experimental"<<endl;
      line(comm->cout());
      firstwarn = false;
    }
    // Pack, write continuous, and then unpack
    F[i]->pack();
    dVector out(F[i]->ndof()+BLOSC_MAX_OVERHEAD);
    int isize = sizeof(Scalar)*F[i]->ndof();
    int osize = sizeof(Scalar)*out.size();
    int csize = blosc_compress(9,1,sizeof(Scalar),
                isize, F[i]->elmt_data.data(), out.data(), osize);
    if(csize==0) {
      comm->cout()<<"Buffer was incompressible"<<endl;
    } else if (csize<0) {
      comm->cout()<<"Compression error in BLOSC with code "<<csize<<endl;
    }
#ifdef DGM_VERBOSE_COMPRESSION
    comm->cout()<<"Compressing "<<F[i]->name<<": "<<isize<<" -> "<<csize<<" ("
                <<(1.*isize)/csize<<"x)"<<endl;
#endif
    const char *c_size = reinterpret_cast<const char*>(&csize);
    fs.write(c_size, sizeof(csize));
    const char *out_data = reinterpret_cast<const char*>(out.data());
    //const streamoff start = fs.tellp();
    fs.write(out_data, csize);
    //comm->cout()<<"Wrote Field "<<F[i]->name<<" at "<<start<<" to "
    //            <<fs.tellp()<<endl;
#ifdef DGM_TEST_BLOSC_COMPRESSION
    // test the compression
    dVector dest(F[i]->ndof(),0);
    int dsize = sizeof(Scalar)*F[i]->ndof();
    dsize = blosc_decompress(out.data(), dest.data(), dsize);
    if (dsize < 0) comm->error("Decompression error");
    for (int k=0; k<F[i]->ndof(); k++) {
      if (dest[k] != F[i]->elmt_data[k]) {
        comm->error("Decompressed data differs from original!");
        break;
      }
    }
#endif
    F[i]->unpack();
#else
    //----------------------------------------
    // this is a hack to write a datafile
    //F[i]->pack();
    //nfs.write(reinterpret_cast<const char*>(F[i]->elmt_data.data()),
    //          sizeof(Scalar)*F[i]->ndof());
    //F[i]->unpack();
    // end of hack
    //----------------------------------------
    for (LocalSize e=0; e<F[i]->ne; e++) {
      fs.write(reinterpret_cast<const char*>(F[i]->el[e]->u.data()),
               sizeof(Scalar) * F[i]->el[e]->nModes());
    }
#endif
  }
  const_cast<vField*>(this)->backward_transform();
#else
  // write in physical space
  for (LocalSize i=0; i<F.size(); i++) {
    fs.write(reinterpret_cast<const char*>(F[i]->elmt_data.data()),
             sizeof(Scalar)*F[i]->elmt_data.size());
  }
#endif
  if (fs.bad()) {
    const unsigned long s = comm->ScratchSize();
    if ( s != numeric_limits<unsigned long>::max())
      cout<<"Size of free space in "<<comm->Path()<<" is "<<s<<" bytes."<<endl;
    comm->error("Error in vField::write(const string &, const streamoff)\n"
                "  Write to file "+fname+" failed. Perhaps the disk is full?");
  }
#ifdef DGM_DEBUG_BLOSC
  blosc_destroy();
  //comm->cout()<<"Finished compressed write at "<<fs.tellp()<<endl;
#endif
  return fs.tellp();
}

//============================================================================
//                        Visualization Output
//============================================================================

/// Output in flat binary format
/** \todo Extend to work in parallel. */
void vField::suplot(const string root, const string fname) const {
  // looks for root.su, if doesn't exist return
  string fname_su = root+".su";
  ifstream in(fname_su.c_str());
  // if root.su exists, read size of export grid = nx ny nz increment of
  // grid = dx dy dz start location = x0 y0 z0 and the field index = Fid
  if (in) {
    comm->cout()<<"  Writing fname_su in SU formats"<<endl;
    FILE *fp;
    fp = fopen(fname.c_str(),"w");
    string buffer;
    int nx, ny, nz;
    Scalar dx, dy, dz;
    Scalar x0, y0, z0;
    int Fid;
    Point ptmp;
    Size elemindex[4];
    Size elenum;
    string fname_mesh;

    // would be good not to have to re-read the mesh every time
    fname_mesh = root+".msh";
    Mesh mesh(fname_mesh);

    getline(in,buffer);        // strip off header line
    const LocalSize nsd = F[1]->nsd();
    if (nsd==1) {
      in >> nx >> dx >> x0 >> Fid;
      comm->cerr() << "ERROR: mesh.find_source_elem only works for 2D or 3d"
                   << endl;
      comm->exit(DGM::FAILURE);
    } else if (nsd==2) {
      in >> nx >> ny >> dx >> dy >> x0 >> y0 >> Fid;
      for(int j=0; j<ny; j++) {
        ptmp.y = y0 + j*dy;
        for(int i=0; i<nx; i++) {
          cout << "  i = " << setw(5) << i << ", j = "
               << setw(4) << j << flush;
          ptmp.x = x0 + i*dx;
          elenum = mesh.find_source_elem(ptmp,elemindex);
          if (elenum==0) comm->error("Element not found for x,y,z point");
          // Note: elenum = number of elements where the node lives
          //       elemindex[0..3] = first four elem ID's
          // Point might live in more than one element, so average values
          Scalar value = 0.0;
          for(Size ei=0; ei<elenum; ei++) {
            Size e = elemindex[ei];
            value = value + F[Fid]->el[e]->interpolate_point(ptmp);
          }
          value = value/float(elenum);
          float outvalue = value;
          fwrite( &outvalue, sizeof(float), 1, fp );
          cout << "\r";
        }
      }
    } else if (nsd==3) {
      in >> nx >> ny >> nz >> dx >> dy >> dz
         >> x0 >> y0 >> z0 >> Fid;
      for(int j=0; j<ny; j++) {
        ptmp.y = y0 + j*dy;
        for(int i=0; i<nx; i++) {
          ptmp.x = x0 + i*dx;
          for(int k=0; k<nz; k++) {
            ptmp.z = z0 + k*dz;
            cout << "  i = " << setw(5) << i << ", j = " << setw(4) << j
                 << ", k = " << setw(4) << k << flush;
            elenum = mesh.find_source_elem_3d(ptmp,elemindex);
            if (elenum==0) comm->error("Element not found for x,y,z point");
            // Note: elenum = number of elements where the node lives
            //       elemindex[0..3] = first four elem ID's
            // Point might live in more than one element, so average values
            Scalar value = 0.0;
            for(Size ei=0; ei<elenum; ei++) {
              Size e = elemindex[ei];
              value = value + F[Fid]->el[e]->interpolate_point(ptmp);
            }
            value = value/float(elenum);
            float outvalue = value;
            fwrite( &outvalue, sizeof(float), 1, fp );
            cout << "\r";
          }
        }
      }
    }
    cout << endl;
    fclose(fp);
  }
}

/// Define to use the Tecplot point format for 1d runs
#define DGM_TECPLOT_POINT
//#define DGM_TECPLOT_1D_GRAD

/// Make a tecplot file from a vField
/** \todo Convert to generate binary Tecplot files
    \todo Extend to work in parallel. */
void vField::tecplot(const string fname, const string title) const {
  const LocalSize nsd = F[0]->nsd();
  FILE *fp;
  fp = fopen(fname.c_str(),"w");
  if(!fp) comm->error("Unable to open file for writing in vField::tecplot.");
  fprintf(fp,"TITLE=\"%s\"\n",title.c_str());
  if (nsd==1) {
#ifdef DGM_TECPLOT_POINT
#ifdef DGM_TECPLOT_1D_GRAD           // Output first variable and its gradient.
    for (size_type i=0; i<size(); i++) {
      fprintf(fp,"VARIABLES=\"x\" \"%s\" \"d%s/dx\"\n",
          F[i]->name.c_str(),F[i]->name.c_str());
      fprintf(fp,"ZONE F=POINT\n");
      for (LocalSize e=0; e<F[i]->ne; e++) F[i]->el[e]->tecplot(fp);
    }
#else                                // Output all the variables.
    fprintf(fp,"VARIABLES=\"x\"");
    for (size_type i=0; i<size(); i++) fprintf(fp,",\"%s\"",F[i]->name.c_str());
    fprintf(fp,"\nZONE F=POINT\n");
    for (LocalSize e=0; e<F[0]->ne; e++) {
      for (Ordinal q=0; q<F[0]->el[e]->qtot; q++) {
        fprintf(fp,"%15.8e ", F[0]->el[e]->C->x[q]);
        for (size_type i=0; i<size(); i++) {
          if (F[i]->el[e]->state == Element::States::Transform)
            throw DGM::exception("Line::output called when in transform space");
          fprintf(fp,"%15.8e ", F[i]->el[e]->u[q]);
        }
        fprintf(fp,"\n");
      }
    }
#endif
#else
    fprintf(fp,"VARIABLES=\"x\"");
    for (int i=0; i<size(); i++) fprintf(fp,",\"%s\"",F[i]->name.c_str());
    for (LocalSize e=0; e<F[0]->ne; e++) {
      fprintf(fp,"\nZONE T=\"Element %d\", I=%d, F=BLOCK",
              partition->eid(F[0]->el[e]->lid()),F[0]->el[e]->qa);
      F[0]->el[e]->output(fp,'x');
      for (int i=0; i<size(); i++) F[i]->el[e]->output(fp);
    }
#endif
  } else if (nsd==2) {
    fprintf(fp,"VARIABLES=\"x\",\"y\"");
    for (size_type i=0; i<size(); i++)
      fprintf(fp,",\"%s\"",F[i]->name.c_str());
    for (LocalSize e=0; e<F[0]->ne; e++) {
      F[0]->el[e]->output(fp,'h');  // Tecplot header
      F[0]->el[e]->output(fp,'x');
      F[0]->el[e]->output(fp,'y');
      for (size_type i=0; i<size(); i++) F[i]->el[e]->output(fp);
      F[0]->el[e]->output(fp,'f');  // Tecplot footer
    }
  } else {
    fprintf(fp,"VARIABLES=\"x\",\"y\",\"z\"");
    for (size_type i=0; i<size(); i++)
      fprintf(fp,",\"%s\"",F[i]->name.c_str());
    for (LocalSize e=0; e<F[0]->ne; e++) {
      F[0]->el[e]->output(fp,'h');  // Tecplot header
      F[0]->el[e]->output(fp,'x');
      F[0]->el[e]->output(fp,'y');
      F[0]->el[e]->output(fp,'z');
      for (size_type i=0; i<size(); i++) F[i]->el[e]->output(fp);
      F[0]->el[e]->output(fp,'f');  // Tecplot footer
    }
  }
  fclose(fp);
}

/// Output a Paraview VTK-XML UnstructuredGrid file in serial and parallel
/** \note When in parallel, the files are place in a .viz directory. */
void vField::paraview_combined(const string name, const string title) const {
  char buf[128];
  string fname;
  if (comm->NumProc()>1) {
    string viz_name = name;
    sprintf(buf,"%s.pvtu",name.c_str()); fname = buf;
    if (comm->Master()) paraview_pvtu(fname,viz_name,comm->NumProc());
    sprintf(buf,"%s.p%d.vtu",viz_name.c_str(),comm->MyPID()); fname = buf;
  } else {
    sprintf(buf,"%s.vtu",name.c_str()); fname = buf;
  }
  paraview_vtu_modified(fname,title);
  comm->Barrier();
}

void vField::paraview_vtu_modified(const string fname,
                                   const string title) const {
#ifdef DGM_BINARY_PARAVIEW
  paraview_vtu_modified_binary(fname,title);
#else
  paraview_vtu_modified_ascii(fname,title);
#endif
}

/// Make a Paraview XML file from a vField (vtu format)
/** \warning Still experimental -- but works for most element types. */
void vField::paraview_vtu_modified_ascii
   (const string fname, const string title) const {
  FILE *fp;
  fp = fopen(fname.c_str(),"w");
  fprintf(fp,"<VTKFile type=\"UnstructuredGrid\" "
          "byte_order=\"LittleEndian\">\n");
  fprintf(fp,"<UnstructuredGrid>\n");
  LocalSize qtotmax = 0;
  for (LocalSize e=0; e<F[0]->ne; e++)
    if (qtotmax < numeric_cast<LocalSize>(F[0]->el[e]->qtot))
      qtotmax = F[0]->el[e]->qtot;
  for (LocalSize e=0; e<F[0]->ne; e++) {
    const Ordinal npts   = F[0]->el[e]->nVerts();
    const Ordinal ncells = 1;
    const std::shared_ptr<Element> clone(F[0]->el[e]->clone());
    clone->qa=clone->qb=clone->qc=2;
    fprintf(fp,"<Piece NumberOfPoints=\"%lld\" NumberOfCells=\"%lld\">\n",
             (long long)npts,(long long)ncells);
    std::string namelist;
    for (LocalSize i=0; i<size(); ++i) namelist += F[i]->name+" ";
    namelist += "Coordinates";
    fprintf(fp,"<CellData Scalars=\"%s\">\n",namelist.c_str());
    for (LocalSize i=0; i<size(); ++i) {
#if 1
      string tmp_s = "<DataArray type=\"Float64\" Name=\"";
      tmp_s += F[i]->name.c_str();
      tmp_s += "\" NumberOfComponents=\"";
      tmp_s += lexical_cast<string>(qtotmax) + "\" Format=\"ascii\">";
      fprintf(fp, "%s", tmp_s.c_str());
#else
      fprintf(fp,"<DataArray type=\"Float64\" "
              "Name=\"%s\" "
              "NumberOfComponents=\"%lu\" "
              "Format=\"ascii\">",
              F[i]->name.c_str(),
              qtotmax);
#endif
      F[i]->el[e]->output(fp);
      for (LocalSize j=F[i]->el[e]->qtot; j<qtotmax; ++j) {
         if (j%5==0) fprintf(fp,"\n");
         fprintf(fp,"0.0 ");
      }
      fprintf(fp,"\n</DataArray>\n");
    }
#if 1
      string tmp_s = "DataArray type=\"Float64\" Name=\"Coordinates\" ";
      tmp_s += "NumberOfComponents=\"" + lexical_cast<string>(3*qtotmax);
      tmp_s += "\" Format=\"ascii\">\n";
      fprintf(fp, "%s", tmp_s.c_str());
#else
    fprintf(fp,"<DataArray type=\"Float64\" "
               "Name=\"Coordinates\" "
               "NumberOfComponents=\"%lu\" "
               "Format=\"ascii\">\n",
                3*qtotmax);
#endif
    F[0]->el[e]->output(fp,'p');
    for (LocalSize j=F[0]->el[e]->qtot; j<qtotmax; ++j) {
       fprintf(fp,"0.0 0.0 0.0\n");
    }
    fprintf(fp,"</DataArray>\n");
    fprintf(fp,"</CellData>\n");

    fprintf(fp,"<Points>\n");
    fprintf(fp,"<DataArray type=\"Float64\" "
               "NumberOfComponents=\"3\" "
               "Format=\"ascii\">\n");
    for (vector<Vertex::Ptr>::size_type i=0; i<clone->vert.size(); ++i) {
       const Vertex::Ptr P = clone->vert[i];
       fprintf(fp,"%15.8e %15.8e %15.8e\n",P->x,P->y,P->z);
    }
    fprintf(fp,"</DataArray>\n");
    fprintf(fp,"</Points>\n");

    fprintf(fp,"<Cells>\n");
    fprintf(fp,"<DataArray type=\"Int32\" Name=\"connectivity\" "
            "Format=\"ascii\">\n");
    for (vector<Vertex::Ptr>::size_type i=0; i<clone->vert.size(); ++i) {
       const int v = numeric_cast<int>(i);
       fprintf(fp,"%d ", v);
    }
    fprintf(fp,"\n</DataArray>\n");
    fprintf(fp,"<DataArray type=\"Int32\" Name=\"offsets\" "
            "Format=\"ascii\">");
    clone->output(fp,'o');
    fprintf(fp,"\n</DataArray>\n");
    fprintf(fp,"<DataArray type=\"UInt8\" Name=\"types\" "
            "Format=\"ascii\">");
    clone->output(fp,'t');
    fprintf(fp,"\n</DataArray>\n");
    fprintf(fp,"</Cells>\n");

    fprintf(fp,"</Piece>\n");
  }
  fprintf(fp,"</UnstructuredGrid>\n");
  fprintf(fp,"</VTKFile>\n");
  fclose(fp);
}

/// Make a Paraview XML file from a vField (vtu format)
/** \warning Still experimental -- but works for most element types. */
void vField::paraview_vtu_modified_binary
  (const string fname, const string title) const {
  FILE *fp;
  streamoff offset = 0;
  fp = fopen(fname.c_str(),"w");
  fprintf(fp,"<VTKFile type=\"UnstructuredGrid\" "
          "byte_order=\"LittleEndian\">\n");
  fprintf(fp,"<UnstructuredGrid>\n");
  for (LocalSize e=0; e<F[0]->ne; e++) {
    const Ordinal npts   = F[0]->el[e]->nVerts();
    const Ordinal ncells = 1;
    fprintf(fp,"<Piece NumberOfPoints=\"%lld\" NumberOfCells=\"%lld\">\n",
             (long long)npts,(long long)ncells);
    fprintf(fp,"<CellData Scalars=\"Scalars\">\n");
    for (size_type i=0; i<size(); ++i) {
      fprintf(fp,"<DataArray type=\"Float32\" Name=\"%s\" "
              "Format=\"appended\" "
              "Offset=\"%lld\" "
              "></DataArray>\n",
              F[i]->name.c_str(),
              (long long)offset);
      offset += F[i]->el[e]->binaryLength(Element::ParaviewBinary);
    }
    fprintf(fp,"<DataArray type=\"Float32\" Name=\"Coordinates\" "
            "NumberOfComponents=\"3\" "
            "Format=\"appended\" "
            "Offset=\"%lld\" "
            "></DataArray>\n",(long long)offset);
    offset += F[0]->el[e]->binaryLength(Element::ParaviewCoordinates);
    fprintf(fp,"</CellData>\n");

    const std::shared_ptr<Element> clone(F[0]->el[e]->clone());
    clone->qa=clone->qb=clone->qc=2;

    fprintf(fp,"<Points>\n");
    fprintf(fp,"<DataArray type=\"Float32\" NumberOfComponents=\"3\" "
            "Format=\"append\" "
            "Offset=\"%lld\" "
            "></DataArray>\n",(long long)offset);
    offset += sizeof(uint32_t) + 3*sizeof(float)*clone->vert.size();

    fprintf(fp,"</Points>\n");
    fprintf(fp,"<Cells>\n");
    fprintf(fp,"<DataArray type=\"Int32\" Name=\"connectivity\" "
            "Format=\"append\" "
            "Offset=\"%lld\" "
            "></DataArray>\n",(long long)offset);
    offset += sizeof(uint32_t) + sizeof(uint32_t)*clone->vert.size();

    fprintf(fp,"<DataArray type=\"Int32\" Name=\"offsets\" "
            "Format=\"append\" "
            "Offset=\"%lld\" "
            "></DataArray>\n",(long long)offset);
    offset += clone->binaryLength(Element::ParaviewOffsets);

    fprintf(fp,"<DataArray type=\"UInt8\" Name=\"types\" "
            "Format=\"append\" "
            "Offset=\"%lld\" "
            "></DataArray>\n",(long long)offset);
    offset += clone->binaryLength(Element::ParaviewTypes);
    fprintf(fp,"</Cells>\n");
    fprintf(fp,"</Piece>\n");
  }
  fprintf(fp,"</UnstructuredGrid>\n");
  fprintf(fp,"<AppendedData encoding=\"raw\">\n_");
  for (LocalSize e=0; e<F[0]->ne; ++e) {
    for (size_type i=0; i<size(); ++i) {
      F[i]->el[e]->binaryOutput(fp,Element::ParaviewBinary);
    }
    F[0]->el[e]->binaryOutput(fp,Element::ParaviewCoordinates);
    const std::shared_ptr<Element> clone(F[0]->el[e]->clone());
    clone->qa=clone->qb=clone->qc=2;
    {
      const uint32_t length =
        3*sizeof(float)*numeric_cast<uint32_t>(clone->vert.size());
      fwrite(&length,sizeof(uint32_t),1,fp);
    }
    for (vector<Vertex::Ptr>::size_type i=0; i<clone->vert.size(); ++i) {
       const Vertex::Ptr P=clone->vert[i];
       float X[3];
       X[0]=P->x; X[1]=P->y; X[2]=P->z;
       fwrite(X,sizeof(float),3,fp);
    }
    {
      const uint32_t length =
        sizeof(uint32_t)*numeric_cast<uint32_t>(clone->vert.size());
      fwrite(&length,sizeof(uint32_t),1,fp);
    }
    for (vector<Vertex::Ptr>::size_type i=0; i<clone->vert.size(); ++i) {
      const uint32_t I = numeric_cast<uint32_t>(i);
      fwrite(&I,sizeof(uint32_t),1,fp);
    }
    clone->binaryOutput(fp,Element::ParaviewOffsets);
    clone->binaryOutput(fp,Element::ParaviewTypes);
  }
  fprintf(fp,"\n</AppendedData>\n");
  fprintf(fp,"</VTKFile>\n");
  fclose(fp);
}

/// Output a Paraview VTK-XML UnstructuredGrid file in serial and parallel
/** \note When in parallel, the files are place in a .viz directory. */
void vField::paraview(const string name, const string title) const {
  char buf[128];
  string fname;
  if (comm->NumProc()>1) {
#ifdef DGM_USE_BOOST_FS
    boost::filesystem::path path(name+".viz");
    if (comm->Master()) boost::filesystem::create_directory(path);
    comm->Barrier();
    string viz_name = name + ".viz/" + name;
#else
    string viz_name = name;
#endif
    sprintf(buf,"%s.pvtu",name.c_str()); fname = buf;
    if (comm->Master()) paraview_pvtu(fname,viz_name,comm->NumProc());
    sprintf(buf,"%s.p%d.vtu",viz_name.c_str(),comm->MyPID()); fname = buf;
  } else {
    sprintf(buf,"%s.vtu",name.c_str()); fname = buf;
  }
  paraview_vtu(fname,title);
  comm->Barrier();
}

/// Use binary Paraview format
#define DGM_BINARY_PARAVIEW

/// Make a Paraview XML file from a vField (vtu format)
/** \warning Still experimental -- but works for most element types. */
void vField::paraview_vtu(const string fname, const string title) const {
  FILE *fp;
#ifdef DGM_BINARY_PARAVIEW
  streamoff offset = 0;
#endif
  fp = fopen(fname.c_str(),"w");
  fprintf(fp,"<VTKFile type=\"UnstructuredGrid\" "
          "byte_order=\"LittleEndian\">\n");
  fprintf(fp,"<UnstructuredGrid>\n");
  for (LocalSize e=0; e<F[0]->ne; e++) {
    const Ordinal ncells = F[0]->el[e]->ncells();
    const Ordinal npts = F[0]->el[e]->qtot;
    fprintf(fp,"<Piece NumberOfPoints=\"%lld\" NumberOfCells=\"%lld\">\n",
            (long long)npts,(long long)ncells);
    fprintf(fp,"<PointData Scalars=\"Scalars\">");
#ifdef DGM_BINARY_PARAVIEW
    for (size_type i=0; i<size(); ++i) {
      fprintf(fp,"\n<DataArray type=\"Float32\" Name=\"%s\" "
              "format=\"appended\" offset=\"%lld\"/>",F[i]->name.c_str(),
              (long long)offset);
      offset+=F[i]->el[e]->binaryLength(Element::ParaviewBinary);
    }
#else
    for (LocalSize i=0; i<size(); ++i) {
      fprintf(fp,"\n<DataArray type=\"Float64\" Name=\"%s\" "
              "Format=\"ascii\">",F[i]->name.c_str());
      F[i]->el[e]->output(fp);
      fprintf(fp,"\n</DataArray>");
    }
#endif
    fprintf(fp,"\n</PointData>\n");
    fprintf(fp,"<Points>\n");
#ifdef DGM_BINARY_PARAVIEW
    fprintf(fp,"<DataArray type=\"Float32\" NumberOfComponents=\"3\" "
            "format=\"appended\" offset=\"%lld\"/>\n",(long long)offset);
    offset+=F[0]->el[e]->binaryLength(Element::ParaviewCoordinates);
#else
    fprintf(fp,"<DataArray type=\"Float64\" NumberOfComponents=\"3\" "
            "Format=\"ascii\">");
    F[0]->el[e]->output(fp,'p');
    fprintf(fp,"\n</DataArray>\n");
#endif
    fprintf(fp,"</Points>\n");
    fprintf(fp,"<Cells>\n");
#ifdef DGM_BINARY_PARAVIEW
    fprintf(fp,"<DataArray type=\"Int32\" Name=\"connectivity\" "
            "format=\"appended\" offset=\"%lld\"/>\n",(long long)offset);
    offset+=F[0]->el[e]->binaryLength(Element::ParaviewConnectivity);
    fprintf(fp,"<DataArray type=\"Int32\" Name=\"offsets\" "
            "format=\"appended\" offset=\"%lld\"/>\n",(long long)offset);
    offset+=F[0]->el[e]->binaryLength(Element::ParaviewOffsets);
    fprintf(fp,"<DataArray type=\"UInt8\" Name=\"types\" "
            "format=\"appended\" offset=\"%lld\"/>\n",(long long)offset);
    offset+=F[0]->el[e]->binaryLength(Element::ParaviewTypes);
#else
    fprintf(fp,"<DataArray type=\"Int32\" Name=\"connectivity\" "
            "Format=\"ascii\">");
    F[0]->el[e]->output(fp,'c');
    fprintf(fp,"\n</DataArray>\n");
    fprintf(fp,"<DataArray type=\"Int32\" Name=\"offsets\" "
            "Format=\"ascii\">");
    F[0]->el[e]->output(fp,'o');
    fprintf(fp,"\n</DataArray>\n");
    fprintf(fp,"<DataArray type=\"UInt8\" Name=\"types\" "
            "Format=\"ascii\">");
    F[0]->el[e]->output(fp,'t');
    fprintf(fp,"\n</DataArray>\n");
#endif
    fprintf(fp,"</Cells>\n");
    fprintf(fp,"</Piece>\n");
  }
  fprintf(fp,"</UnstructuredGrid>\n");
#ifdef DGM_BINARY_PARAVIEW
  fprintf(fp,"<AppendedData encoding=\"raw\">\n_");
  for (LocalSize e=0; e<F[0]->ne; ++e) {
    for (size_type i=0; i<size(); ++i) {
      F[i]->el[e]->binaryOutput(fp,Element::ParaviewBinary);
    }
    F[0]->el[e]->binaryOutput(fp,Element::ParaviewCoordinates);
    F[0]->el[e]->binaryOutput(fp,Element::ParaviewConnectivity);
    F[0]->el[e]->binaryOutput(fp,Element::ParaviewOffsets);
    F[0]->el[e]->binaryOutput(fp,Element::ParaviewTypes);
  }
  fprintf(fp,"\n</AppendedData>\n");
#endif
  fprintf(fp,"</VTKFile>\n");
  fclose(fp);
}

/// Make a Paraview XML file from a vField (parallel vtu format
/** \warning Still experimental -- but works for most element types. */
void vField::paraview_pvtu(const string fname, const string name,
                           const int Npieces) const {
  char buf[128];
  FILE *fp;
  fp = fopen(fname.c_str(),"w");
  fprintf(fp,"<VTKFile type=\"PUnstructuredGrid\">\n");
  fprintf(fp,"<PUnstructuredGrid GhostLevel=\"0\">\n");
  fprintf(fp,"<PPointData Scalars=\"Scalars\">");
#ifdef DGM_BINARY_PARAVIEW
  for (size_type i=0; i<size(); ++i) {
    fprintf(fp,"\n<PDataArray type=\"Float32\" Name=\"%s\" "
            "Format=\"appended\">",F[i]->name.c_str());
    fprintf(fp,"\n</PDataArray>");
  }
  fprintf(fp,"\n</PPointData>\n");
  fprintf(fp,"<PPoints>\n");
  fprintf(fp,"<PDataArray type=\"Float32\" NumberOfComponents=\"3\" "
          "Format=\"appended\">");
  fprintf(fp,"\n</PDataArray>\n");
  fprintf(fp,"</PPoints>\n");
#else
  for (LocalSize i=0; i<size(); ++i) {
    fprintf(fp,"\n<PDataArray type=\"Float64\" Name=\"%s\" "
            "Format=\"ascii\">",F[i]->name.c_str());
    fprintf(fp,"\n</PDataArray>");
  }
  fprintf(fp,"\n</PPointData>\n");
  fprintf(fp,"<PPoints>\n");
  fprintf(fp,"<PDataArray type=\"Float64\" NumberOfComponents=\"3\" "
          "Format=\"ascii\">");
  fprintf(fp,"\n</PDataArray>\n");
  fprintf(fp,"</PPoints>\n");
#endif
  string source;
  for (int n=0; n<Npieces; ++n) {
    sprintf(buf,"%s.p%d.vtu",name.c_str(),n); source = buf;
    fprintf(fp,"<Piece Source=\"%s\"/>\n",source.c_str());
  }
  fprintf(fp,"</PUnstructuredGrid>\n");
  fprintf(fp,"</VTKFile>\n");
  fclose(fp);
}

#ifdef DGM_PARALLEL

namespace {
/// Quadrature dimensions in 3d
struct QuadDim {
  int qa;
  int qb;
  int qc;
};
/// Quadrature dimensions in 2d
struct QuadDim2d {
  int qa;
  int qb;
};
}

/// Make a multi-grid Plot3d grid file from a vField using MPI-IO
void vField::MPI_plot3d_x2d(const string fname, const MPI_Offset skip) const {
  //comm->cout() << "vField::MPI_plot3d_x2d()" << endl;
  const int nsd = F[0]->nsd();
  assert(nsd==2);

  char native[] = "native";
  MPI_File fh;
  MPI_Status status;
  MPI_Offset disp = skip;  // absolute offset in bytes from the beginning

  MPI_Info info;
  MPI_Info_create(&info);

  MPI_Comm mpicomm = dynamic_cast<const DGM::MpiComm*>(comm.get())->mpi_comm;

  //comm->cout() << "  About to open file " << fname << endl;

  if (MPI_File_open(mpicomm, const_cast<char*>(fname.c_str()),
                    MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &fh)) {
    throw exception(string("MPI_File_open failed to open file " + fname));
  }
  // comm->cout() << "  File opened" << endl;
  // MPI_File_set_atomicity(fh, 1);

  // write global number of elements
  int gne = partition->gne();
  // MPI_Barrier(mpicomm);
  MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, native, info);
  MPI_File_write_all(fh, &gne, 1, MPI_INT, &status);
  disp += sizeof(int);

  // comm->cout() << "  Wrote number of elements = " << partition->gne << endl;
  std::vector<QuadDim2d> quadDim(partition->ne());
  for (size_t e=0; e<quadDim.size(); ++e) {
    quadDim[e].qa = F[0]->el[e]->qa;
    quadDim[e].qb = F[0]->el[e]->qb;
  }

  // make filetype for mesh sizes
  MPI_Datatype quadtype;
  MPI_Type_contiguous(nsd,MPI_INT,&quadtype);
  MPI_Type_commit(&quadtype);

  MPI_Datatype inttype;
  intVector ilen(partition->ne()); ilen = 1;
  {
    std::vector<MPI_Aint> bytes(partition->ne());
    for (LocalSize i=0; i<partition->ne(); ++i)
      bytes[i]=partition->eid(i)*nsd*sizeof(int);
    MPI_Type_create_hindexed(partition->ne(), ilen.data(),
                             &bytes.front(), quadtype, &inttype);
  }

  MPI_Type_commit(&inttype);

  // MPI_Barrier(mpicomm);
  MPI_File_set_view(fh, disp, quadtype, inttype, native, info);
  MPI_File_write_all(fh,&(quadDim.front()),partition->ne(),quadtype,&status);
  disp += partition->gne()*sizeof(QuadDim2d);
  MPI_Type_free(&inttype);
  MPI_Type_free(&quadtype);
  // comm->cout() << "  Finished writing mesh dimensions" << endl;

  // make type for data
  const LocalSize ne  = partition->ne();
  intVector L(ne);
  intVector D(ne);
  D = 0; L = 0;
  int len  = 0;
  for (LocalSize e=0; e<ne; ++e) L[e] = nsd*partition->nodal_len[e];
  for (LocalSize e=0; e<ne; ++e) len += L[e];
  GlobalSize glen = 0;
  partition->global_scan(glen,D,L);

  MPI_Datatype filetype;
  {
    std::vector<MPI_Aint> bytes(ne);
    for (LocalSize i=0; i<ne; ++i) bytes[i]=D[i]*sizeof(float);
    MPI_Type_create_hindexed(ne, L.ptr(), &bytes.front(), MPI_FLOAT, &filetype);
  }
  MPI_Type_commit(&filetype);

  const int nodal_len = partition->nodal_disp[ne-1] - partition->nodal_disp[0]
    + partition->nodal_len[ne-1];

  cout<<comm->MyPID()<<": nodal_len  = "<<nodal_len<<endl;
  cout<<comm->MyPID()<<": nsd*nodal_len  = "<<nsd*nodal_len<<endl;
  cout<<comm->MyPID()<<": F[0].ndof() = "<<F[0]->ndof()<<endl;
  cout<<comm->MyPID()<<": F[0].qtot() = "<<F[0]->qtot()<<endl;
  cout<<comm->MyPID()<<": nodal_glen = "<<partition->nodal_glen()<<endl;
  cout<<comm->MyPID()<<": nsd*nodal_glen = "<<nsd*partition->nodal_glen()<<endl;
  cout<<comm->MyPID()<<": glen = "<<glen<<endl;
  cout<<comm->MyPID()<<": len = "<<len<<endl;

  CMC::Vector<float,int> tmp(nsd*nodal_len);
  int m=0;
  for (LocalSize e=0; e<F[0]->ne; e++) {
    const int qa = F[0]->el[e]->qa;
    const int qb = F[0]->el[e]->qb;
    const dVector &x = F[0]->el[e]->C->x;
    const dVector &y = F[0]->el[e]->C->y;
    for (int j=0; j<qb; j++) {
      for (int i=0; i<qa; i++) {
        const int q = j + i*qb;
        tmp[m++] = (float)x[q];
      }
    }
    for (int j=0; j<qb; j++) {
      for (int i=0; i<qa; i++) {
        const int q = j + i*qb;
        tmp[m++] = (float)y[q];
      }
    }
  }
  // MPI_Barrier(mpicomm);
  MPI_File_set_view(fh, disp, MPI_FLOAT, filetype, native, info);
  MPI_File_write_all(fh, tmp.ptr(), nsd*nodal_len, MPI_FLOAT, &status);
  disp += nsd*partition->nodal_glen()*sizeof(float);

  MPI_File_close(&fh);
  MPI_Type_free(&filetype);
  MPI_Info_free(&info);
}

/// Make a multi-grid Plot3d grid file from a vField using MPI-IO
void vField::MPI_plot3d_x(const string fname, const MPI_Offset skip) const {
  // comm->cout() << "vField::MPI_plot3d_x()" << endl;
  const int nsd = F[0]->nsd();
#if 0
  if (nsd==2) {
    MPI_plot3d_x2d(fname,skip);
    return;
  }
#endif
  assert(nsd==2 || nsd==3);

  char native[] = "native";
  MPI_File fh;
  MPI_Status status;
  MPI_Offset disp = skip;  // absolute offset in bytes from the beginning

  MPI_Info info;
  MPI_Info_create(&info);

  MPI_Comm mpicomm = dynamic_cast<const DGM::MpiComm*>(comm.get())->mpi_comm;

  // comm->cout() << "  About to open file " << fname << endl;
  if (MPI_File_open(mpicomm, const_cast<char*>(fname.c_str()),
                    MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &fh)) {
    throw exception(string("MPI_File_open failed to open file " + fname));
  }
  // comm->cout() << "  File opened" << endl;
  // MPI_File_set_atomicity(fh, 1);

  // write global number of elements
  int gne = partition->gne();
  // MPI_Barrier(mpicomm);
  MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, native, info);
  MPI_File_write_all(fh, &gne, 1, MPI_INT, &status);
  disp += sizeof(int);
  // comm->cout() << "  Wrote number of elements = " << partition->gne << endl;

  std::vector<QuadDim> quadDim(partition->ne());
  for (size_t e=0; e<quadDim.size(); ++e) {
    quadDim[e].qa = F[0]->el[e]->qa;
    quadDim[e].qb = F[0]->el[e]->qb;
  }
  if (nsd<3) {
    for (size_t e=0; e<quadDim.size(); ++e) {
      quadDim[e].qc = 2;
    }
  } else {
    for (size_t e=0; e<quadDim.size(); ++e) {
      quadDim[e].qc = F[0]->el[e]->qc;
    }
  }

  // make filetype for mesh sizes
  MPI_Datatype quadtype;
  MPI_Type_contiguous(3,MPI_INT,&quadtype);
  MPI_Type_commit(&quadtype);

  MPI_Datatype inttype;
  intVector ilen(partition->ne()); ilen = 1;
  {
    std::vector<MPI_Aint> bytes(partition->ne());
    for (LocalSize i=0; i<partition->ne(); ++i)
      bytes[i]=partition->eid(i)*3*sizeof(int);
    MPI_Type_create_hindexed(partition->ne(), ilen.data(),
                             &bytes.front(), quadtype, &inttype);
  }
  MPI_Type_commit(&inttype);

  // MPI_Barrier(mpicomm);
  MPI_File_set_view(fh, disp, quadtype, inttype, native, info);
  MPI_File_write_all(fh, &(quadDim.front()), partition->ne(),
                     quadtype, &status);
  disp += partition->gne()*sizeof(QuadDim);
  MPI_Type_free(&inttype);
  MPI_Type_free(&quadtype);

  // comm->cout() << "  Finished writing mesh dimensions" << endl;

  // make type for data
  const LocalSize ne  = partition->ne();
  intVector L(ne);
  intVector D(ne);
  D = 0; L = 0;
  int len = 0;
  const int fact = 3*(nsd==2 ? 2 : 1);
  for (LocalSize e=0; e<ne; ++e) L[e] = fact*partition->nodal_len[e];
  for (LocalSize e=0; e<ne; ++e) len += L[e];
  GlobalSize glen = 0;
  partition->global_scan(glen,D,L);

  MPI_Datatype filetype;
  {
    std::vector<MPI_Aint> bytes(ne);
    for (LocalSize i=0; i<ne; ++i) bytes[i]=D[i]*sizeof(float);
    MPI_Type_create_hindexed(ne, L.ptr(), &bytes.front(), MPI_FLOAT, &filetype);
  }
  MPI_Type_commit(&filetype);

  // const int nodal_len = partition->nodal_disp[ne-1] -
  // partition->nodal_disp[0] + partition->nodal_len[ne-1];
#if 0
  cout<<comm->MyPID()<<": nodal_len  = "<<nodal_len<<endl;
  cout<<comm->MyPID()<<": fact*nodal_len  = "<<fact*nodal_len<<endl;
  cout<<comm->MyPID()<<": F[0].ndof  = "<<F[0]->ndof<<endl;
  cout<<comm->MyPID()<<": F[0].qtot()  = "<<F[0]->qtot<<endl;
  cout<<comm->MyPID()<<": nodal_glen = "<<partition->nodal_glen()<<endl;
  cout<<comm->MyPID()<<": fact*nodal_glen = "<<fact*partition->nodal_glen()
      <<endl;
  cout<<comm->MyPID()<<": len = "<<len<<endl;
#endif

  CMC::Vector<float,int> tmp(len);

  if (nsd==2) {
    int m=0;
    for (LocalSize e=0; e<F[0]->ne; e++) {
      const int qa = F[0]->el[e]->qa;
      const int qb = F[0]->el[e]->qb;
      const int qc = 2;
      const dVector &x = F[0]->el[e]->C->x;
      const dVector &y = F[0]->el[e]->C->y;
      for (int k=0; k<qc; k++) {
        for (int j=0; j<qb; j++) {
          for (int i=0; i<qa; i++) {
            const int q = j + i*qb;
            tmp[m++] = (float)x[q];
          }
        }
      }
      for (int k=0; k<qc; k++) {
        for (int j=0; j<qb; j++) {
          for (int i=0; i<qa; i++) {
            const int q = j + i*qb;
            tmp[m++] = (float)y[q];
          }
        }
      }
      for (int k=0; k<qc; k++) {
        for (int j=0; j<qb; j++) {
          for (int i=0; i<qa; i++) {
            tmp[m++] = (float)k;
          }
        }
      }
    }
  } else {
    int m=0;
    for (LocalSize e=0; e<F[0]->ne; e++) {
      const int qa = F[0]->el[e]->qa;
      const int qb = F[0]->el[e]->qb;
      const int qc = F[0]->el[e]->qc;
      const dVector &x = F[0]->el[e]->C->x;
      const dVector &y = F[0]->el[e]->C->y;
      const dVector &z = F[0]->el[e]->C->z;
      for (int k=0; k<qc; k++) {
        for (int j=0; j<qb; j++) {
          for (int i=0; i<qa; i++) {
            const int q = k + j*qc + i*qb*qc;
            tmp[m++] = (float)x[q];
          }
        }
      }
      for (int k=0; k<qc; k++) {
        for (int j=0; j<qb; j++) {
          for (int i=0; i<qa; i++) {
            const int q = k + j*qc + i*qb*qc;
            tmp[m++] = (float)y[q];
          }
        }
      }
      for (int k=0; k<qc; k++) {
        for (int j=0; j<qb; j++) {
          for (int i=0; i<qa; i++) {
            const int q = k + j*qc + i*qb*qc;
            tmp[m++] = (float)z[q];
          }
        }
      }
    }
  }
  // MPI_Barrier(mpicomm);
  MPI_File_set_view(fh, disp, MPI_FLOAT, filetype, native, info);
  MPI_File_write_all(fh, tmp.ptr(), len, MPI_FLOAT, &status);
  disp += glen*sizeof(float);

  MPI_File_close(&fh);
  MPI_Type_free(&filetype);
  MPI_Info_free(&info);
}

/// Make a multi-grid Plot3d Q-file file from a vField in parallel
void vField::MPI_plot3d_q(const string fname,
                          const Scalar mach, const Scalar alpha,
                          const Scalar reyn, const Scalar time) const {
  const int nsd = F[0]->nsd();
  assert(nsd==2 || nsd==3);

  char native[] = "native";
  MPI_File fh;
  MPI_Status status;
  MPI_Offset disp = 0;  // absolute offset in bytes from the beginning

  MPI_Info info;
  MPI_Info_create(&info);

  MPI_Comm mpicomm = dynamic_cast<const DGM::MpiComm*>(comm.get())->mpi_comm;

  // comm->cout() << "  About to open file " << fname << endl;
  if (MPI_File_open(mpicomm, const_cast<char*>(fname.c_str()),
                    MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &fh)) {
    throw exception(string("MPI_File_open failed to open file " + fname));
  }
  // comm->cout() << "  File opened" << endl;
  // MPI_File_set_atomicity(fh, 1);

  // write global number of elements
  int gne = partition->gne();
  // MPI_Barrier(mpicomm);
  MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, native, info);
  MPI_File_write_all(fh, &gne, 1, MPI_INT, &status);
  disp += sizeof(int);
  // comm->cout() << "  Wrote number of elements = " << partition->gne << endl;

  std::vector<QuadDim> quadDim(partition->ne());
  for (size_t e=0; e<quadDim.size(); ++e) {
    quadDim[e].qa = F[0]->el[e]->qa;
    quadDim[e].qb = F[0]->el[e]->qb;
  }
  if (nsd<3) {
    for (size_t e=0; e<quadDim.size(); ++e) {
      quadDim[e].qc = 2;
    }
  } else {
    for (size_t e=0; e<quadDim.size(); ++e) {
      quadDim[e].qc = F[0]->el[e]->qc;
    }
  }

  // make filetype for mesh sizes
  MPI_Datatype quadtype;
  MPI_Type_contiguous(3,MPI_INT,&quadtype);
  MPI_Type_commit(&quadtype);

  MPI_Datatype inttype;
  intVector ilen(partition->ne()); ilen = 1;
  {
    std::vector<MPI_Aint> bytes(partition->ne());
    for (LocalSize i=0; i<partition->ne(); ++i)
      bytes[i]=partition->eid(i)*3*sizeof(int);
    if (int stat = MPI_Type_create_hindexed(partition->ne(), ilen.data(),
                                            &bytes.front(), MPI_INT,
                                            &inttype))
      comm->error("MPI_Type_hindexed", stat);
  }
  MPI_Type_commit(&inttype);

  // MPI_Barrier(mpicomm);
  MPI_File_set_view(fh, disp, quadtype, inttype, native, info);
  MPI_File_write_all(fh, &(quadDim.front()), partition->ne(),
                     quadtype, &status);
  disp += partition->gne()*sizeof(QuadDim);
  MPI_Type_free(&inttype);
  MPI_Type_free(&quadtype);

  // comm->cout() << "  Finished writing mesh dimensions" << endl;

  // make type for data
  const LocalSize ne = partition->ne();
  intVector L(ne);
  intVector D(ne);
  D = 0; L = 0;
  int len  = 0;
  const int fact = 5*(nsd==2 ? 2 : 1);
  for (LocalSize e=0; e<ne; ++e) L[e] = 4 + fact*partition->nodal_len[e];
  for (LocalSize e=0; e<ne; ++e) len += L[e];
  GlobalSize glen = 0;
  partition->global_scan(glen,D,L);

  MPI_Datatype filetype;
  {
    std::vector<MPI_Aint> bytes(ne);
    for (LocalSize i=0; i<ne; ++i) bytes[i]=D[i]*sizeof(float);
    MPI_Type_create_hindexed(ne, L.ptr(), &bytes.front(), MPI_FLOAT, &filetype);
  }
  MPI_Type_commit(&filetype);

  CMC::Vector<float,int> tmp(len);

  if (nsd==2) {
    int m=0;
    for (LocalSize e=0; e<ne; e++) {
      const int qa = F[0]->el[e]->qa;
      const int qb = F[0]->el[e]->qb;
      const int qc = 2;
      tmp[m++] = (float)mach;
      tmp[m++] = (float)alpha;
      tmp[m++] = (float)reyn;
      tmp[m++] = (float)time;
      for (size_t n=0; n<5; n++) {
        for (int k=0; k<qc; k++) {
          for (int j=0; j<qb; j++) {
            for (int i=0; i<qa; i++) {
              const int q = j + i*qb;
              const size_t nl = min(F.size()-1,n);
              tmp[m++] = (float)(F[nl]->el[e]->u[q]);
            }
          }
        }
      }
    }
  } else {
    int m=0;
    for (LocalSize e=0; e<ne; e++) {
      tmp[m++] = (float)mach;
      tmp[m++] = (float)alpha;
      tmp[m++] = (float)reyn;
      tmp[m++] = (float)time;
      for (size_t n=0; n<5; n++) {
        for (Ordinal k=0; k<F[0]->el[e]->qc; k++) {
          for (Ordinal j=0; j<F[0]->el[e]->qb; j++) {
            for (Ordinal i=0; i<F[0]->el[e]->qa; i++) {
              const int q = k + j*F[0]->el[e]->qc +
                i*F[0]->el[e]->qb*F[0]->el[e]->qc;
              const size_t nl = min(F.size()-1,n);
              tmp[m++] = (float)(F[nl]->el[e]->u[q]);
            }
          }
        }
      }
    }
  }
  // MPI_Barrier(mpicomm);
  MPI_File_set_view(fh, disp, MPI_FLOAT, filetype, native, info);
  MPI_File_write_all(fh, tmp.ptr(), len, MPI_FLOAT, &status);
  disp += glen*sizeof(float);

  MPI_File_close(&fh);
  MPI_Type_free(&filetype);
  MPI_Info_free(&info);
}

#endif // DGM_PARALLEL

/// Make a multi-grid Plot3d grid file from a vField
void vField::plot3d_x(const string fname) const {
#ifdef DGM_PARALLEL
  MPI_plot3d_x(fname);
  return;
#endif
  LocalSize nsd = F[0]->nsd();
  const int two = 2;
  FILE *fp;
  fp = fopen(fname.c_str(),"w");
  const int ine = numeric_cast<int>(F[0]->ne);
  fwrite( &ine, sizeof(int), 1, fp );
  for (LocalSize e=0; e<F[0]->ne; e++) {
    if (F[0]->el[e]->qb) {  // qb = 0 for NodalTri and NodalTet
      const int iqa = numeric_cast<int>(F[0]->el[e]->qa);
      fwrite( &iqa, sizeof(int), 1, fp );
      const int iqb = numeric_cast<int>(F[0]->el[e]->qb);
      fwrite( &iqb, sizeof(int), 1, fp );
      if (nsd < 3) {
        fwrite( &two, sizeof(int), 1, fp );
      } else {
        const int iqc = numeric_cast<int>(F[0]->el[e]->qc);
        fwrite( &iqc, sizeof(int), 1, fp );
      }
    } else { // NodalTri or NodalTet
      throw DGM::exception("Plot3d output not supported for NodalTri");
    }
  }
  LocalSize q;
  float tmp;
  if (nsd == 3 ) {
    for (LocalSize e=0; e<F[0]->ne; e++) {
      for (LocalSize k=0; k<F[0]->el[e]->qc; k++)
        for (LocalSize j=0; j<F[0]->el[e]->qb; j++)
          for (LocalSize i=0; i<F[0]->el[e]->qa; i++) {
            q = k + j*F[0]->el[e]->qc + i*F[0]->el[e]->qb*F[0]->el[e]->qc;
            tmp = (float)(F[0]->el[e]->C->x[q]);
            fwrite( &tmp, sizeof(float), 1, fp);
          }
      for (LocalSize k=0; k<F[0]->el[e]->qc; k++)
        for (LocalSize j=0; j<F[0]->el[e]->qb; j++)
          for (LocalSize i=0; i<F[0]->el[e]->qa; i++) {
            q = k + j*F[0]->el[e]->qc + i*F[0]->el[e]->qb*F[0]->el[e]->qc;
            tmp = (float)(F[0]->el[e]->C->y[q]);
            fwrite( &tmp, sizeof(float), 1, fp);
          }
      for (LocalSize k=0; k<F[0]->el[e]->qc; k++)
        for (LocalSize j=0; j<F[0]->el[e]->qb; j++)
          for (LocalSize i=0; i<F[0]->el[e]->qa; i++) {
            q = k + j*F[0]->el[e]->qc + i*F[0]->el[e]->qb*F[0]->el[e]->qc;
            tmp = (float)(F[0]->el[e]->C->z[q]);
            fwrite( &tmp, sizeof(float), 1, fp);
          }
    }
  } else if (nsd == 2) {
    for (LocalSize e=0; e<F[0]->ne; e++) {
      if (F[0]->el[e]->qb) { // qb = 0 for NodalTri
        for (LocalSize k=0; k<2; k++)
          for (LocalSize j=0; j<F[0]->el[e]->qb; j++)
            for (LocalSize i=0; i<F[0]->el[e]->qa; i++) {
              q = j + i*F[0]->el[e]->qb;
              tmp = (float)(F[0]->el[e]->C->x[q]);
              fwrite( &tmp, sizeof(float), 1, fp);
            }
        for (LocalSize k=0; k<2; k++)
          for (LocalSize j=0; j<F[0]->el[e]->qb; j++)
            for (LocalSize i=0; i<F[0]->el[e]->qa; i++) {
              q = j + i*F[0]->el[e]->qb;
              tmp = (float)(F[0]->el[e]->C->y[q]);
              fwrite( &tmp, sizeof(float), 1, fp);
            }
        for (LocalSize k=0; k<2; k++)
          for (LocalSize j=0; j<F[0]->el[e]->qb; j++)
            for (LocalSize i=0; i<F[0]->el[e]->qa; i++) {
              q = j + i*F[0]->el[e]->qb;
              tmp = (float)k;
              fwrite( &tmp, sizeof(float), 1, fp);
            }
      } else { // NodalTri
        throw DGM::exception("Plot3d output not supported for NodalTri");
      }
    }
  } else {
    cerr << "vField::plot3d_x -- illegal value of nsd = " << nsd << endl;
    comm->exit(DGM::FAILURE);
  }
  fclose(fp);
}

/// Make a multi-grid Plot3d Q-file file from a vField
void vField::plot3d_q(const string fname,
                      const Scalar mach, const Scalar alpha,
                      const Scalar reyn, const Scalar time) const {
#ifdef DGM_PARALLEL
  MPI_plot3d_q(fname,mach,alpha,reyn,time);
  return;
#endif
  const LocalSize nsd = F[0]->nsd();
  const int two = 2;
  FILE *fp;
  fp = fopen(fname.c_str(),"w");
  const int ine = numeric_cast<int>(F[0]->ne);
  fwrite( &ine, sizeof(int), 1, fp );
  for (LocalSize e=0; e<F[0]->ne; e++) {
    if (F[0]->el[e]->qb) {            // qb = 0 for NodalTri and NodalTet
      const int iqa = numeric_cast<int>(F[0]->el[e]->qa);
      fwrite( &iqa, sizeof(int), 1, fp );
      const int iqb = numeric_cast<int>(F[0]->el[e]->qb);
      fwrite( &iqb, sizeof(int), 1, fp );
      if (nsd < 3) {
        fwrite( &two, sizeof(int), 1, fp );
      } else {
        const int iqc = numeric_cast<int>(F[0]->el[e]->qc);
        fwrite( &iqc, sizeof(int), 1, fp );
      }
    } else {
      throw DGM::exception("Plot3d output not supported for NodalTri");
    }
  }
  LocalSize q;
  float tmp;
  for (LocalSize e=0; e<F[0]->ne; e++) {
    // flow conditions
    tmp = (float)mach;
    fwrite( &tmp, sizeof(float), 1, fp);
    tmp = (float)alpha;
    fwrite( &tmp, sizeof(float), 1, fp);
    tmp = (float)reyn;
    fwrite( &tmp, sizeof(float), 1, fp);
    tmp = (float)time;
    fwrite( &tmp, sizeof(float), 1, fp);
    if (nsd == 3) {
      for (size_t n=0; n<5; n++) {
        for (LocalSize k=0; k<F[0]->el[e]->qc; k++)
          for (LocalSize j=0; j<F[0]->el[e]->qb; j++)
            for (LocalSize i=0; i<F[0]->el[e]->qa; i++) {
              q = k + j*F[0]->el[e]->qc + i*F[0]->el[e]->qb*F[0]->el[e]->qc;
              size_t nl = min(F.size()-1,n);
              tmp = (float)(F[nl]->el[e]->u[q]);
              fwrite( &tmp, sizeof(float), 1, fp);
            }
      }
    } else if (nsd == 2) {
      if (F[0]->el[e]->qb) { // qb = 0 for NodalTri
        for (size_t n=0; n<3; n++) {
          for (LocalSize k=0; k<2; k++)
            for (LocalSize j=0; j<F[0]->el[e]->qb; j++)
              for (LocalSize i=0; i<F[0]->el[e]->qa; i++) {
                q = j + i*F[0]->el[e]->qb;
                size_t nl = min(F.size()-1,n);
                tmp = (float)(F[nl]->el[e]->u[q]);
                fwrite( &tmp, sizeof(float), 1, fp);
              }
        }
        size_t n = 3;
        for (LocalSize k=0; k<2; k++)
          for (LocalSize j=0; j<F[0]->el[e]->qb; j++)
            for (LocalSize i=0; i<F[0]->el[e]->qa; i++) {
              q = j + i*F[0]->el[e]->qb;
              tmp = 0.0;
              fwrite( &tmp, sizeof(float), 1, fp);
            }
        for (LocalSize k=0; k<2; k++)
          for (LocalSize j=0; j<F[0]->el[e]->qb; j++)
            for (LocalSize i=0; i<F[0]->el[e]->qa; i++) {
              q = j + i*F[0]->el[e]->qb;
              size_t nl = min(F.size()-1,n);
              tmp = (float)(F[nl]->el[e]->u[q]);
              fwrite( &tmp, sizeof(float), 1, fp);
            }
      } else { // NodalTri
        throw DGM::exception("Plot3d output not supported for NodalTri");
      }
    } else {
      cerr << "vField::plot3d_q -- illegal value of nsd = " << nsd << endl;
      comm->exit(DGM::FAILURE);
    }
  }
  fclose(fp);
}

//============================================================================
//                         Local I/O routines
//============================================================================

/// Returns true if file named fname exists
bool vField::local_exists(const string &fname) const {
  ifstream fs(fname.c_str());
  return fs.good();
}

/// Read a vField locally on each node
/** Local_read is identical to read in serial but in parallel does not do
    MPI-IO so that each node reads it's part of a file individually, usually
    from it's own local filesystem or memory. */
streamoff vField::local_read(const string &fname, const streamoff offset,
                             const bool saved_as_float) {
  ifstream fs(fname.c_str());
  fs.seekg(offset);                      // position file pointer at offset
  return local_read(fs, saved_as_float);
}

/// Read a vField locally on each node
/** Local_read is identical to read in serial but in parallel does not do
    MPI-IO so that each node reads it's part of a file individually, usually
    from it's own local filesystem or memory. */
streamoff vField::local_read(istream &fs, const bool saved_as_float) {
#ifdef DGM_FIELD_TRANSFORM
  // read in transform space
  for (size_t i=0; i<F.size(); i++) {
    int glen;
    intVector L(F[i]->ne), D(F[i]->ne);
    // read global data length
    fs.read(reinterpret_cast<char*>(&(glen)),sizeof(int));
    // read element data lengths
    for (LocalSize e=0; e<F[i]->ne; e++)
      fs.read(reinterpret_cast<char*>(&(L[e])),sizeof(int));
    // get element data displacements
    for (LocalSize e=0; e<F[i]->ne; e++)
      fs.read(reinterpret_cast<char*>(&(D[e])),sizeof(int));
    // read the data
    for (LocalSize e=0; e<F[i]->ne; e++) {
      F[i]->el[e]->zero();
      dVector tmp(L[e]);
      if (saved_as_float && sizeof(Scalar) != sizeof(float)) {
        std::vector<float> float_data(L[e]);
        fs.read(reinterpret_cast<char*>(&float_data[0]),sizeof(float)*L[e]);
        for (int i=0; i<L[e]; ++i) tmp[i] = float_data[i];
      } else {
        fs.read(reinterpret_cast<char*>(tmp.data()),sizeof(Scalar)*L[e]);
      }
#ifdef DGM_VFIELD_LOCAL_READ_ENFORCE_CONFORMITY
      // use this if you want to enforce conformity
      if (L[e] != F[i]->el[e]->nModes())
        throw DGM::exception(asString(comm->MyPID())+": tried to read a "
        "nonconformal element on field "+asString(i)+" for global element "+
        asString(partition->eid(e)));
#endif
      F[i]->el[e]->set(tmp,L[e]);
    }
  }
  backward_transform();
#else
  // read in physical space
  for (vField::size_type i=0; i<F.size(); i++)
    if (saved_as_float && sizeof(Scalar) != sizeof(float)) {
      const int ndof = numeric_cast<int>(F[i]->elmt_data.size());
      std::vector<float> float_data(ndof);
      fs.read(reinterpret_cast<char*>(&float_data[0]),sizeof(float)*ndof);
      Scalar *tmp = F[i]->elmt_data.data();
      for (int i=0; i<ndof; ++i) tmp[i] = float_data[i];
    } else {
      fs.read(reinterpret_cast<char*>(F[i]->elmt_data.data()),
              sizeof(Scalar)*F[i]->elmt_data.size());
    }
#endif
  return fs.tellg();
}


/// Write the vField locally on each node
/** Local_write is identical to write in serial but in parallel does not do
    MPI-IO so that each node writes it's part of a file individually, usually
    to it's own local filesystem or to memory. */
streamoff vField::local_write(const string &fname, const streamoff offset,
                              const bool save_as_float) const {
#if 1
  // This seems to work better
  ofstream fs(fname.c_str(), ios::app);  // append to file
#else
  fstream fs(fname.c_str(), ios::in|ios::out);
  fs.seekp(offset);                      // position file pointer at offset
#endif
  return local_write(fs, save_as_float);
}

/// write vector field data in one big block
#define DGM_VFIELD_BLOCK_WRITE

/// Write a vField locally on each node
/** Local_write is identical to write in serial but in parallel does not do
    MPI-IO so that each node writes it's part of a file individually, usually
    to it's own local filesystem or to memory. */
streamoff vField::local_write(ostream &fs, const bool save_as_float) const {
#ifdef DGM_FIELD_TRANSFORM
  // write in transform space
  const_cast<vField*>(this)->forward_transform();
  for (size_t i=0; i<F.size(); i++) {
    // write global data length
    const int ndof = numeric_cast<int>(F[i]->ndof());
    fs.write(reinterpret_cast<const char*>(&ndof),sizeof(int));
    // write data lengths
    for (LocalSize e=0; e<F[i]->ne; e++) {
      const int nModes = numeric_cast<int>(F[i]->el[e]->nModes());
      fs.write(reinterpret_cast<const char*>(&nModes),sizeof(int));
    }
    // write data displacements
    int disp = 0;
    for (LocalSize e=0; e<F[i]->ne; e++) {
      fs.write(reinterpret_cast<const char*>(&disp),sizeof(int));
      disp += numeric_cast<int>(F[i]->el[e]->nModes());
    }
    // write the data
#ifdef DGM_VFIELD_BLOCK_WRITE
    // as one big block
    F[i]->pack();
    if (save_as_float && sizeof(Scalar) != sizeof(float)) {
      const int ndof = numeric_cast<int>(F[i]->ndof());
      const Scalar *data = F[i]->elmt_data.data();
      const std::vector<float> float_data(data, data+ndof);
      const char *C = reinterpret_cast<const char*>(&float_data[0]);
      fs.write(C, sizeof(float)*ndof);
    } else {
      fs.write(reinterpret_cast<const char*>(F[i]->elmt_data.data()),
               sizeof(Scalar)*numeric_cast<int>(F[i]->ndof()));
    }
    F[i]->unpack();
#else
    // as individual elements
    if (save_as_float && sizeof(Scalar) != sizeof(float)) {
      for (LocalSize e=0; e<F[i]->ne; e++) {
        const int ndof = numeric_cast<int>(F[i]->el[e]->nModes());
        const Scalar *data = F[i]->el[e]->u.data();
        const std::vector<float> float_data(data, data+ndof);
        const char *C = reinterpret_cast<const char*>(&float_data[0]);
        fs.write (C, sizeof(float)*ndof);
      }
    } else {
      for (LocalSize e=0; e<F[i]->ne; e++)
        fs.write(reinterpret_cast<const char*>(F[i]->el[e]->u.data()),
                 sizeof(Scalar)*numeric_cast<int>(F[i]->el[e]->nModes()));
    }
#endif
  }
  const_cast<vField*>(this)->backward_transform();
#else
  // write in physical space (as one big block)
  for (LocalSize i=0; i<F.size(); i++) {
    if (save_as_float && sizeof(Scalar) != sizeof(float)) {
      const int ndof = numeric_cast<int>(F[i]->elmt_data.size());
      const Scalar *data = F[i]->elmt_data.data();
      const std::vector<float> float_data(data, data+ndof);
      const char *C = reinterpret_cast<const char*>(&float_data[0]);
      fs.write (C, sizeof(float)*ndof);
    } else {
      fs.write(reinterpret_cast<const char*>(F[i]->elmt_data.data()),
               sizeof(Scalar)*numeric_cast<int>(F[i]->elmt_data.size()));
    }
  }
#endif
  if (fs.bad()) {
    const long s = comm->ScratchSize();
    if ( s != numeric_limits<long>::max())
      cout<<"Size of free space in "<<comm->Path()<<" is "<<s<<" bytes."<<endl;
    comm->error("Error in vField::local_write.\n"
                "Write to file failed.  Perhaps the disk is full?");
  }
  return fs.tellp();
}

//============================================================================
//                        Trilinos::Epetra support
//============================================================================

#ifdef DGM_USE_EPETRA

/// Helper function taken from Epetra_VbrMatrix.
/** Shouldn't be needed once Epetra supports an Epetra_BlockOperator
    interface. */
Teuchos::RCP<Epetra_Map> vField::BlockMap2PointMap(
    const Epetra_BlockMap &BlockMap ) {
  int MaxElementSize = BlockMap.MaxElementSize();
  int PtNumMyElements = BlockMap.NumMyPoints();
  int *PtMyGlobalElements = 0;
  if (PtNumMyElements>0) PtMyGlobalElements = new int[PtNumMyElements];
  int NumMyElements = BlockMap.NumMyElements();
  int curID = 0;
  for (int i=0; i<NumMyElements; i++) {
    int startID = BlockMap.GID(i)*MaxElementSize;
    int ElementSize = BlockMap.ElementSize(i);
    for (int j=0; j<ElementSize; j++)
      PtMyGlobalElements[curID++] = startID+j;
  }
  assert(curID==PtNumMyElements);
  Teuchos::RCP<Epetra_Map> PointMap =
      Teuchos::rcp(new Epetra_Map(-1, PtNumMyElements,
          PtMyGlobalElements,
          BlockMap.IndexBase(),
          BlockMap.Comm() ));
  if (PtNumMyElements>0) delete[] PtMyGlobalElements;
  if (!BlockMap.PointSameAs(*PointMap))
    DGM::Comm::World->error("Incompatible maps in Operator");
  return PointMap;
}

void vField::gather_column_dofs() {
  // Note to myself (agerste): why not exporting this information using
  // the Exporter?? Partial answer: so we don't have to send this via MPI, we
  // can just reconstruct this information at any time.
  cdof_per_ele.clear();
  for (size_t ifield = 0; ifield < F.size(); ++ifield) {
    for (size_t e = 0; e < F[ifield]->el.size(); ++e) {
      const Element *const ele = F[ifield]->el[e];
      const int nmodes = ele->nModes();
      if (ifield == 0) {
        cdof_per_ele[ele->gid()] = vector<int>(0);
        cdof_per_ele[ele->gid()].reserve(nmodes*F.size()); // <- just a guess
      }
      for (int imode = 0; imode < nmodes; ++imode) {
        const int gid = ele->gid();
        assert(DofPerFieldEle().find(gid) != DofPerFieldEle().end() );
        const int dofGID = DofPerFieldEle().find(gid)->second[ifield][imode];
        assert(dofGID >= 0);
        cdof_per_ele[gid].push_back(dofGID);
      }
    }
  }

  for (size_t ifield = 0; ifield < F.size(); ++ifield) {
    for (map<int,Element*>::const_iterator e =
        F[ifield]->GhostElementMap().begin();
        e != F[ifield]->GhostElementMap().end(); ++e) {
      const Element *const ele = e->second;
      const int nmodes = ele->nModes();
      if (ifield == 0) {
        assert(cdof_per_ele.find(ele->gid()) == cdof_per_ele.end() );
        cdof_per_ele[ele->gid()] = vector<int>(0);
        cdof_per_ele[ele->gid()].reserve(nmodes*F.size()); // <- just a guess
      }
      for (int imode = 0; imode < nmodes; ++imode) {
        const int gid = ele->gid();
        assert(DofPerFieldEle().find(gid) != DofPerFieldEle().end() );
        const int dofGID = DofPerFieldEle().find(gid)->second[ifield][imode];
        assert(dofGID >= 0);
        cdof_per_ele[gid].push_back(dofGID);
      }
    }
  }
  return;
}

const vector<int>& vField::get_row_elem_dofs(const int egid) const {
  map<int,vector<int> >::const_iterator entry= rdof_per_ele.find(egid);
  if (entry == rdof_per_ele.end()) {
    ostringstream s;
    s << "vField::get_row_elem_dofs(egid): "
        << "No DOF indices found for element with GID " << egid << "!" << endl;
    for (map<int,vector<int> >::const_iterator i = rdof_per_ele.begin();
        i != rdof_per_ele.end(); i++) {
      cout << i->first << endl;
      cout << i->second.size() << endl;
    }
    comm->error(s.str());
  }
  const vector<int>& dofs = entry->second;
  return dofs;
}

const vector<int>& vField::get_col_elem_dofs(const int egid) const {
  map<int,vector<int> >::const_iterator entry= cdof_per_ele.find(egid);
  if (entry == cdof_per_ele.end()) {
    ostringstream s;
    s << "vField::get_col_elem_dofs(egid): "
        << "No DOF indices found for element with GID " << egid << "!" << endl;
    for (map<int,vector<int> >::const_iterator i = cdof_per_ele.begin();
        i != cdof_per_ele.end(); i++) {
      cout << i->first << endl;
      cout << i->second.size() << endl;
    }
    comm->error(s.str());
  }
  const vector<int>& dofs = entry->second;
  return dofs;
}

void vField::init_redistribution_framework(const Epetra_Comm& Comm) {
  for (size_type i=0; i<size(); i++) {
    F[i]->init_redistribution_framework(Comm);
  }
}

void vField::ghost_aura() {
  for (size_type i=0; i<size(); i++) {
    F[i]->ghost_aura();
  }
#ifdef DGM_USE_GENERAL_GHOSTING
  // export DOF layout
  DGM::Exporter exporter(*F[0]->row_element_map(),
                         *F[0]->col_element_map(), *comm);
  exporter.Export(dof_per_fieldele);
#else
  throw DGM::exception("Requires DGM_USE_GENERAL_GHOSTING");
#endif
}

/// Ghost only once
/** Background: I can't do element ghosting in the Domain constructor,
    because if the Field copy constructor is used to clone Fields,
    it won't have ghost elements, which subsequentially leads to a failure,
    when set_side_links is called. So the failure can be explained, but as long
    as I don't integrate the ghost elements in the Field copy constructor,
    this is a quick fix to avoid ghosting multiple times.  You can now just
    call this ghost method in the Domain::solve() method. (agerste) */
void vField::ghost(const string& root, const Scalar z_offset) {
  if (not F[0]->GhostElementMap().empty()) return;
  init_redistribution_framework(RowDofMapPtr()->Comm());
  gather_column_dofs();
  if (comm->NumProc() == 1) return;
  comm->cout() << "Ghosting " << name << endl;
  ghost_aura();
  gather_column_dofs(); // redo
  comm->Barrier();
}

/// This method ghosts element data of ghost elements
/*!
 *  It is kind of equivalent to a call to share_sides()
 */
void vField::share_ghost_element_data() const {
#ifdef DGM_USE_GENERAL_GHOSTING
  assert(F[0]->col_element_map() != NULL);
  map<int,vector<Scalar> > elementdof;
  map<int,Element::States > elementstate;
  for (size_t ifield=0; ifield<F.size(); ifield++) {
    for (size_t e = 0; e < F[ifield]->el.size(); ++e) {
      const Element *const ele = F[ifield]->el[e];
      const int qtot = ele->qtot;
      if (ifield == 0) {
        elementdof[ele->gid()] = vector<Scalar>(0);
        elementdof[ele->gid()].reserve(qtot*F.size()); // <- just a guess
      }
      // send the state
      elementstate[ele->gid()] = ele->state;
      assert(ele->state == Element::Physical or
             ele->state == Element::Transform);
      // assuming uh is aliased to u, we always send u
      for (int iq = 0; iq < qtot; ++iq) {
        elementdof[ele->gid()].push_back(ele->u[iq]);
      }
    }
  }
  // re-shuffle
#ifdef DGM_USE_GENERAL_GHOSTING
  DGM::Exporter exporter(*F[0]->row_element_map(),
                         *F[0]->col_element_map(), *comm);
  exporter.Export(elementdof);
  exporter.Export(elementstate);
#else
  throw DGM::exception("Requires DGM_USE_GENERAL_GHOSTING");
#endif
  // resize and alias ghost elements u and uh, fill it with ghost data
  for (map<int,vector<Scalar> >::const_iterator iter = elementdof.begin();
       iter != elementdof.end();
       iter++) {
    const int gid = iter->first;
    const vector<Scalar> &dofs = iter->second;
    if (not F[0]->row_element_map()->MyGID(gid)) {
      int ildof = 0;
      for (size_t ifield = 0; ifield < F.size(); ++ifield) {
        Element *const ele = F[ifield]->GetGhostElement(gid);
        ele->state = elementstate.find(gid)->second;
        ele->u.resize(ele->qtot); // don't use continuous data for ghost elems
        ele->uh.alias( ele->u, ele->nModes() );
        for (Ordinal iq = 0; iq < ele->qtot; ++iq) {
          ele->u[iq] = dofs[ildof];
          ildof++;
        }
      }
    }
  }
  // resize u of ghost element sides, fill it with ghost element data note. we
  // have to resize u on the side, because DGM_CONTIGUOUS is always on so we
  // loose data and size information
  for (size_t ifield = 0; ifield < F.size(); ++ifield) {
    for (map<int,Element*>::const_iterator iter =
        F[ifield]->GhostElementMap().begin();
        iter != F[ifield]->GhostElementMap().end();
        iter++) {
      Element *const ele = iter->second;
      assert(ele != NULL);
      for (Ordinal iside=0; iside<ele->nSides(); iside++) {
        Side *s = ele->side[iside];
        s->u.resize(s->qtot());
      }
    }
  }
#endif // DGM_USE_GENERAL_GHOSTING
}

/// copy the data from a Elements modal vector into Epetra_Vector
void vField::pack(Epetra_Vector& x) const {
  const int F_size = numeric_cast<int>(F.size());
  for (int ifield =0; ifield!=F_size; ifield++) {
    for (size_t iele=0; iele < F[ifield]->el.size(); iele++) {
      const Element *const ele = F[ifield]->el[iele];
      assert(ele->state == Element::Transform);
      const vector<int> &eledofGIDs = DofPerFieldEle(ele->gid(), ifield);
      const Ordinal numdof = numeric_cast<Ordinal>(eledofGIDs.size());
      for (Ordinal idof=0; idof != numdof; idof++) {
        const int gid = eledofGIDs[idof];
        const int lid = RowDofMapPtr()->LID(gid);
        if (lid == -1) comm->error("vField::unpack: unknown not present!");
        x[lid] = ele->uh[idof];
      }
    }
  }
}

/// copy the data from a Epetra_Vector into Elements modal vector
void vField::unpack(const Epetra_Vector& x) {
  const int F_size = numeric_cast<int>(F.size());
  for (int ifield =0; ifield!=F_size; ifield++) {
    for (size_t iele=0; iele < F[ifield]->el.size(); iele++) {
      Element *const ele = F[ifield]->el[iele];
      assert(ele->state == Element::Transform);
      const vector<int> &eledofGIDs = DofPerFieldEle(ele->gid(), ifield);
      const Ordinal numdof = numeric_cast<Ordinal>(eledofGIDs.size());
      for (Ordinal idof=0; idof != numdof; idof++) {
        const int gid = eledofGIDs[idof];
        const int lid = RowDofMapPtr()->LID(gid);
        if (lid == -1) {
          comm->error("vField::unpack: unknown not present!");
        }
        ele->uh[idof] = x[lid];
      }
    }
  }
}

#endif  // DGM_USE_EPETRA

/** Fill the components of a vector field from an input stream using
    the DGM::Parser.  Allow for continuation using "\".
    This will optionally also fill the sides using the parser too.

    \param[in,out] in  input file stream to read expressions from
    \param[in]     fname name of the file attached to stream
    \param[in]     fill_sides true if you also want to evaluate on sides
    \param[in]     start      index of first field to start evaluation
    \param[in]     end        index of last field, 0 goes to the end

    \note We might be able to split this and use separate fill and fill_sides
          methods
    \note Currently time, t, is set to zero but this would be better to
          generalize
**/
void vField::fill( ifstream &in, const string fname, const bool fill_sides,
                   vField::size_type start, vField::size_type end) {
  if (end==0) end = size();
  for (size_type i=start; i<end; ++i) {
    string buffer;
    if (!getline(in,buffer)) {
      stringstream msg;
      msg << "vField(ifstream) Error initializing " << i
          << "th variable from " << fname;
      comm->error(msg.str());
    }
    string::size_type loc = buffer.find(":=");
    if (loc == std::string::npos) {
      stringstream msg;
      msg<<"vField::fill(ifstream):  Did not find := required for inline "
           "parser for field index "<<i;
      if (!fname.empty()) msg << ", in file '" << fname << "'";
      msg << ".\n  buffer = '" << buffer << "'";
      comm->error(msg.str());
    }
    // Move to the point after the := token
    loc += 2;
    string expr = buffer.substr(loc);
    // Allow for continuation lines
    string::size_type cont = std::string::npos;
    while ( (cont=expr.find("\\")) != std::string::npos) {
      expr.erase(expr.begin()+cont,expr.end());
      if (!getline(in,buffer)) {
        stringstream msg;
        msg << "vField(ifstream) Error reading after continuation character "
            << "for the " << i << "th variable";
        if (!fname.empty()) msg << " from " << fname;
        comm->error(msg.str());
      }
      expr += buffer;
    }
#if 0
    expr = "a=1.0; b=PI;; ; \\ \
            1.0 - cos(a*b*x) * cos(a*b*y);";
#endif
#ifdef DGM_PARSER_DEBUG
    cout<<"vField::fill(in,...) expression  = "<<expr<<endl;
#endif
    // this makes sense for an initial condition but not in other situations
    Scalar t = 0.0;
    for (Field::LocalSize e=0; e<F[i]->ne; e++) {
      F[i]->el[e]->fill(expr);
      if (fill_sides) {
        for (Ordinal n=0; n<F[i]->el[e]->nSides(); n++) {
          const Ordinal sid  = F[i]->el[e]->side[n]->id();
          const Ordinal qtot = F[i]->el[e]->side[n]->qtot();
          Point *pside = new Point[qtot];
          F[i]->el[e]->get_side_coordinates(sid, pside);
          dVector x(qtot), y(qtot), z(qtot);
          for (Ordinal q=0; q<qtot; q++) {
            x[q] = pside[q].x;
            if (nsd()>1) y[q] = pside[q].y;
            if (nsd()>2) z[q] = pside[q].z;
          }
          parser_init();
          if (nsd()==1) {
            Parser::VectorFunction f("x", "t", buffer.substr(loc));
            f.evaluate( x, F[i]->el[e]->side[n]->u, t );
          } else if (nsd()==2) {
            Parser::VectorFunction f("x", "y", "t", buffer.substr(loc));
            f.evaluate( x, y, F[i]->el[e]->side[n]->u, t );
          } else if (nsd()==3) {
            Parser::VectorFunction f("x", "y", "z", "t", buffer.substr(loc));
            f.evaluate( x, y, z, F[i]->el[e]->side[n]->u, t );
          } else {
            comm->error("vField::fill(ifstream) Illegal value of nsd");
          }
          delete[] pside;
        }
      }
    }
  }
  // do not reuse temporaries
  parser_clean();
}

} // namespace DGM
