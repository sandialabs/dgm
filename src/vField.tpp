#ifndef DGM_VFIELD_TPP
#define DGM_VFIELD_TPP

/** \file vField.tpp
    \brief Provides a vector of Field objects (template implementations)
    \author Scott Collis
    \copyright (c)2014 Sandia National Laboratories

    Currently the methods implemented in this file are used to support
    the [BLOSC](http://www.blosc.org) compression library.

    \todo These templated methods need to be corrected to work with general
          data-types.
*/

// Blosc includes (used for data compression)
#ifdef DGM_USE_BLOSC
#include "blosc.h"
#endif

// DGM includes
#include "vField.hpp"
#include "CompressionStats.hpp"

namespace DGM {

/// Read a vField locally on each node using compression
/** \todo Needs to be updated to work with correct datatypes */
template <typename fileScalar>
streamoff vField::compressed_local_read(istream &fs, const Json::Value &json) {
#ifndef DGM_USE_BLOSC
  if (typeid(fileScalar) == typeid(float))
    return local_read(fs,true);
  else if (typeid(fileScalar) == typeid(double))
    return local_read(fs,false);
  else
    throw std::logic_error("Unsupported data type in compressed_local_read");
#else
  typedef int fileLocal;
  typedef LocalSize myLocal;
  typedef Scalar myScalar;
  const string compressor = json["Method"].asString();
  const int verb = json.get("Verbosity",0).asInt();
  blosc_init();
  const int comp = blosc_set_compressor(compressor.c_str());
  if (comp<0) comm->error("Could not set compression scheme:  "+compressor+
      "\n  Available compressors are:  blosclz, lz4, lz4hc, snappy, zlib"+
      "\n  see the BLOSC documentation: http://www.blosc.org for details.");
#ifdef DGM_FIELD_TRANSFORM
  // read in transform space
  for (size_t n=0; n<F.size(); n++) {
    int glen;
    intVector L(F[n]->ne), D(F[n]->ne);
    fs.read(reinterpret_cast<char*>(&(glen)),sizeof(int));
    for (LocalSize e=0; e<F[n]->ne; e++)
      fs.read(reinterpret_cast<char*>(&(L[e])),sizeof(int));
    for (LocalSize e=0; e<F[n]->ne; e++)
      fs.read(reinterpret_cast<char*>(&(D[e])),sizeof(int));
    fileLocal csize = 0;
    char *c_size = reinterpret_cast<char*>(&csize);
    fs.read(c_size,sizeof(csize));
    //comm->cout()<<"Field: "<<F->name<<", csize = "<<csize<<endl;
    std::vector<char> ctmp(csize);
    //const streamoff start = fs.tellg();
    fs.read(reinterpret_cast<char*>(&(ctmp[0])), csize);
    //comm->cout()<<"Read Field "<<F->name<<" at "<<start<<" to "
    //            <<fs.tellg()<<endl;
    const myLocal ndof = F[n]->ndof();
    myLocal dsize = ndof*sizeof(fileScalar);
    CMC::Vector<fileScalar, myLocal> tmp(ndof, 0.0);
    dsize = blosc_decompress(&(ctmp[0]), tmp.data(), dsize);
    if (verb) {
      fileLocal min_csize=0, max_csize=0;
      comm->MaxAll(&csize,&max_csize,1);
      comm->MinAll(&csize,&min_csize,1);
      myLocal min_dsize=0, max_dsize=0;
      comm->MaxAll(&dsize,&max_dsize,1);
      comm->MinAll(&dsize,&min_dsize,1);
      double factor = (1.0*dsize)/csize;
      double min_factor=0, max_factor=0, avg_factor=0;
      comm->MinAll(&factor,&min_factor,1);
      comm->MaxAll(&factor,&max_factor,1);
      comm->SumAll(&factor,&avg_factor,1);
      avg_factor /= (double)comm->NumProc();
      comm->cout()<<"Decompressing "<<F[n]->name<<": "
                  <<"["<<min_dsize<<","<<max_dsize<<"] -> "
                  <<"["<<min_csize<<","<<max_csize<<"] ("<<avg_factor<<"x)"
                  <<endl;
    }
    if (verb>1)
      comm->cout()<<"Decompressing "<<F[n]->name<<": "<<dsize<<" <- "
                  <<csize<<" ("<<(1.*dsize)/csize<<"x)"<<endl;
    assert(dsize==numeric_cast<myLocal>(ndof*sizeof(fileScalar)));
    for (myLocal e=0, k=0; e<F[n]->ne; e++) {
      const myLocal l = numeric_cast<myLocal>(L[e]);
      CMC::Vector<myScalar, myLocal> FtoM(l);
      for (myLocal i=0; i<l; ++i,++k) FtoM[i] = numeric_cast<myScalar>(tmp[k]);
      F[n]->el[e]->zero();
      F[n]->el[e]->set(FtoM,l);
    }
  }
  backward_transform();
#else
#error vField::compressed_local_read() requires DGM_FIELD_TRANSFORM be defined.
#endif
  blosc_destroy();
  return fs.tellg();
#endif
}

/// Write a vField locally on each node using compression
/** \todo Need to update to use the correct datatypes.
 *  \todo Fix the output of float
 */
template <typename fileScalar>
streamoff vField::compressed_local_write(ostream &fs,
                                         const Json::Value &json) const {
  static CompressionStats compStats;
#ifndef DGM_USE_BLOSC
  if (typeid(fileScalar) == typeid(float))
    return local_write(fs,true);
  else if (typeid(fileScalar) == typeid(double))
    return local_write(fs,false);
  else
    throw std::logic_error("compressed_local_write:: Unsupported data type");
#else
  //comm->cout()<<"compressed_local_write(istream &)"<<endl;
  if (typeid(fileScalar)!=typeid(double))
    comm->error("DGM::vField::compressed_local_write() only works for double "
        "right now.  Set:\n\t\"Save as single precision\" : false\n"
        "  in the Json input to remove this error.");
  const string compressor = json["Method"].asString();
  const int level = json.get("Level",9).asInt();
  const int shuffle = json.get("Shuffle",1).asInt();
  const int verb = json.get("Verbosity",0).asInt();
  const int comp = blosc_set_compressor(compressor.c_str());
  blosc_init();
  if (comp<0) comm->error("Could not set compression scheme:  "+compressor+
      "\n  Available compressors are:  blosclz, lz4, lz4hc, snappy, zlib"+
      "\n  see the BLOSC documentation: http://www.blosc.org for details.");
#ifdef DGM_FIELD_TRANSFORM
  // write in transform space
  const_cast<vField*>(this)->forward_transform();
  for (size_t n=0; n<F.size(); n++) {
    const int ndof = numeric_cast<int>(F[n]->ndof());
    fs.write(reinterpret_cast<const char*>(&ndof),sizeof(int));
    for (LocalSize e=0; e<F[n]->ne; e++) {
      const int nModes = numeric_cast<int>(F[n]->el[e]->nModes());
      fs.write(reinterpret_cast<const char*>(&nModes),sizeof(int));
    }
    int disp = 0;
    for (LocalSize e=0; e<F[n]->ne; e++) {
      fs.write(reinterpret_cast<const char*>(&disp),sizeof(int));
      disp += numeric_cast<int>(F[n]->el[e]->nModes());
    }
    F[n]->pack();
    // need to add conversion logic here
    dVector out(F[n]->ndof()+BLOSC_MAX_OVERHEAD);
    size_t isize = sizeof(Scalar)*F[n]->ndof();
    size_t osize = sizeof(Scalar)*out.size();
    int csize = blosc_compress(level,shuffle,sizeof(Scalar), isize,
                               F[n]->elmt_data.data(), out.data(), osize);
    if(csize==0) {
      comm->cout()<<"Buffer was incompressible"<<endl;
    } else if (csize<0) {
      comm->cout()<<"Compression error in BLOSC with code "<<csize<<endl;
    }
    // Summary statistics
    compStats.update(comm,F[n]->name,isize,csize);
    // Aggregated details
    if (verb>1) {
      int min_csize=0, max_csize=0;
      comm->MaxAll(&csize,&max_csize,1);
      comm->MinAll(&csize,&min_csize,1);
      size_t min_isize=0, max_isize=0;
      comm->MaxAll(&isize,&max_isize,1);
      comm->MinAll(&isize,&min_isize,1);
      double factor = (1.0*isize)/csize;
      double min_factor=0, max_factor=0, avg_factor=0;
      comm->MinAll(&factor,&min_factor,1);
      comm->MaxAll(&factor,&max_factor,1);
      comm->SumAll(&factor,&avg_factor,1);
      avg_factor /= (double)comm->NumProc();
      comm->cout()<<"Compressing "<<F[n]->name<<": "
                  <<"["<<min_isize<<","<<max_isize<<"] -> "
                  <<"["<<min_csize<<","<<max_csize<<"] ("<<avg_factor<<"x)"
                  <<endl;
    }
    // Details on every rank
    if (verb>2)
      comm->cout()<<comm->MyPID()<<": Compressing "<<F[n]->name<<": "
                  <<isize<<" -> "<<csize<<" ("<<(1.*isize)/csize<<"x)"<<endl;
    const char *c_size = reinterpret_cast<const char*>(&csize);
    fs.write(c_size, sizeof(csize));
    const char *out_data = reinterpret_cast<const char*>(out.data());
    //const streamoff start = fs.tellp();
    fs.write(out_data, csize);
    //comm->cout()<<"Wrote Field "<<F[n]->name<<" at "<<start<<" to "
    //            <<fs.tellp()<<endl;
#ifdef DGM_TEST_BLOSC_COMPRESSION
    // test the compression
    dVector dest(F[n]->ndof(),0);
    int dsize = sizeof(Scalar)*F[n]->ndof();
    dsize = blosc_decompress(out.data(), dest.data(), dsize);
    if (dsize < 0) comm->error("Decompression error");
    for (int k=0; k<F[n]->ndof(); k++) {
      if (dest[k] != F[n]->elmt_data[k]) {
        comm->error("Decompressed data differs from original!");
        break;
      }
    }
#endif
    F[n]->unpack();
  }
  const_cast<vField*>(this)->backward_transform();
  if (verb) compStats.output(comm);
#else
#error compressed_local_write() requires DGM_FIELD_TRANSFORM be defined.
#endif
  if (fs.bad()) {
    const long s = comm->ScratchSize();
    if ( s != numeric_limits<long>::max())
      cout<<"Size of free space in "<<comm->Path()<<" is "<<s<<" bytes."<<endl;
    comm->error("Error in vField::local_write.\n"
                "Write to file failed.  Perhaps the disk is full?");
  }
  blosc_destroy();
  return fs.tellp();
#endif
}

} // namespace DGM

#endif  // DGM_VFIELD_TPP
