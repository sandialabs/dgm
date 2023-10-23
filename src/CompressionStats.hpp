#ifndef DGM_COMPRESSION_STATS_HPP
#define DGM_COMPRESSION_STATS_HPP

/**
  *  \file CompressionStats.hpp
  *  \brief Compute and display statistics from compression
  *  \author Scott Collis
  *
  *  Created on: Jul 4, 2015
  *      Author: sscoll
  */

// DGM includes
#include "Comm.hpp"
#include "Format.hpp"

namespace DGM {

/// Keeps track of statistics for compression during vField I/O
class CompressionStats {
  class Stats {
  public:
    size_t samples;
    int min_csize, max_csize, gmax_csize;
    size_t min_isize, max_isize, gmax_isize;
    double min_factor, max_factor, avg_factor;
    double gmin_factor, gmax_factor;
    Stats() :
      samples(0),
      min_csize(numeric_limits<int>::max()),
      max_csize(numeric_limits<int>::min()),
      gmax_csize(numeric_limits<int>::min()),
      min_isize(numeric_limits<size_t>::max()),
      max_isize(numeric_limits<size_t>::min()),
      gmax_isize(numeric_limits<size_t>::min()),
      min_factor(numeric_limits<double>::max()),
      max_factor(numeric_limits<double>::min()),
      avg_factor(0),
      gmin_factor(numeric_limits<double>::max()),
      gmax_factor(numeric_limits<double>::min()) {}
  };
  typedef map<string,Stats> dbType;
  dbType db;
public:
  CompressionStats() {}
  ~CompressionStats() {
    // temporarily turn off summary output so tests
    // don't hang trying to output to Comm::World
    // summary(DGM::Comm::World);
  }
  void output(const DGM::Comm::Ptr comm) {
    static Format sci(2,9,'e');
    comm->cout()<<"Compression statistics:"<<endl;
    for (dbType::iterator i=db.begin(); i!=db.end(); ++i) {
      const Stats &s = i->second;
      comm->cout()<<"Field "<<i->first<<": "
          <<"["<<s.min_isize<<","<<s.max_isize<<"] -> "
          <<"["<<s.min_csize<<","<<s.max_csize<<"] "
          <<"["<<sci(s.min_factor)<<","<<sci(s.avg_factor)<<","
               <<sci(s.max_factor)<<"] "
          <<"("<<s.gmax_csize<<","<<sci(s.gmin_factor)<<"x)";
      comm->cout()<<endl;
    }
  }
  void summary(const DGM::Comm::Ptr comm) {
    static Format sci(2,4,'f');
    int sum_csize=0;
    line(comm->cout());
    comm->cout()<<"Compression statistics summary:"<<endl;
    line(comm->cout());
    for (dbType::iterator i=db.begin(); i!=db.end(); ++i) {
      const Stats &s = i->second;
      sum_csize += s.gmax_csize;
      comm->cout()<<"Field "<<i->first<<": "<<s.gmax_csize<<" B, "
                  <<sci(s.gmin_factor)<<"x";
      comm->cout()<<endl;
    }
    comm->cout()<<"Sum of all Fields: " <<sum_csize<<" B"<<endl;
    line(comm->cout());
    comm->Barrier();
  }
  void update(const DGM::Comm::Ptr comm, const string &name,
              const size_t isize, const int csize) {
    Stats &stats = db[name];
    stats.samples++;
    comm->MaxAll(&csize,&stats.max_csize,1);
    comm->MinAll(&csize,&stats.min_csize,1);
    comm->MaxAll(&isize,&stats.max_isize,1);
    comm->MinAll(&isize,&stats.min_isize,1);
    const double factor = (1.0*isize)/csize;
    comm->MinAll(&factor,&stats.min_factor,1);
    comm->MaxAll(&factor,&stats.max_factor,1);
    comm->SumAll(&factor,&stats.avg_factor,1);
    stats.avg_factor /= (double)comm->NumProc();
    stats.gmin_factor = min(stats.min_factor,stats.gmin_factor);
    stats.gmax_factor = max(stats.max_factor,stats.gmax_factor);
    stats.gmax_csize = max(stats.max_csize,stats.gmax_csize);
#ifdef DGM_DETAILED_COMPRESSION_STATS
    comm->cout()<<"Compressing "<<name<<": "
                <<"["<<stats.min_isize<<","<<stats.max_isize<<"] -> "
                <<"["<<stats.min_csize<<","<<stats.max_csize<<"] "
                <<"("<<stats.avg_factor<<"x)"<<endl;
#endif
  }
};

} // namespace DGM

#endif /* DGM_COMPRESSION_STATS_HPP */
