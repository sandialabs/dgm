/**  \file Statistics.hpp
     \brief Base class for computing statistics based on solutions
     \author S. Scott Collis
*/

#ifndef DGM_STATISTICS_HPP
#define DGM_STATISTICS_HPP

// system includes
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// DGM includes
#include "Comm.hpp"

namespace DGM {

  /// Base statistics class
  class Statistics {
  public:
    /// Provides a nice means to describe the statistics
    struct Description {
      std::string name;
      std::string description;
      Description() {}
      Description(const std::string &_name, const std::string &_desc) :
        name(_name), description(_desc) {}
    };
    typedef std::map<std::string,Scalar> DataType;
    typedef DataType::iterator iterator;
    typedef DataType::const_iterator const_iterator;
    typedef std::map<std::string,Description> NameType;
    typedef NameType::iterator name_iterator;
    typedef NameType::const_iterator const_name_iterator;
    typedef std::list<std::string> OrderType;
    typedef OrderType::iterator order_iterator;
    typedef OrderType::const_iterator const_order_iterator;
  protected:
    mutable ofstream os;          ///< output stream
    DataType data;                ///< stores the current statistics data
    NameType names;               ///< names and descriptions of data
    OrderType order;              ///< order of insertion of the keys
    int numberOfSamples;          ///< number of output samples
    int flushFrequency;           ///< how often to flush stream
    const DGM::Comm::Ptr comm;    ///< parallel communicator
    string fileName;              ///< output filename
  public:
    Statistics(const DGM::Comm::Ptr _comm = DGM::Comm::World) :
      numberOfSamples(0), flushFrequency(1), comm(_comm),
      fileName("stats.out") {
      if (comm->Master()) os.open(fileName.c_str(),std::ofstream::app);
    }
    Statistics(string _fname, const DGM::Comm::Ptr _comm = DGM::Comm::World) :
      numberOfSamples(0), flushFrequency(1), comm(_comm), fileName(_fname) {
      if (comm->Master()) os.open(fileName.c_str(),std::ofstream::app);
    }
    virtual ~Statistics() {}
    virtual inline void set(const DataType &in) {
      for (const_iterator it=in.begin(); it!=in.end(); ++it) {
        data[it->first] = it->second;
      }
      increment();
    };
    virtual inline void update(const std::string &key, const Scalar value) {
      data.at(key) = value;
    }
    virtual inline void setup(const std::string &key,
        const Scalar value, const std::string &_name,
        const std::string &_desc) {
      if (data.find(key) != data.end())
        throw DGM::exception("Tried to setup statistic "+key+
        " multiple times");
      order.push_back(key);
      data[key] = value;
      names[key] = Description(_name,_desc);
    }
#define DGM_STATISTICS_ORDERED
    virtual inline void write() const {
      static Format sci(11,18,'e');
      static bool firstTime(true);
#ifdef DGM_STATISTICS_ORDERED
      if (firstTime) {
        if (comm->Master()) {
          os << "# ";
          for (OrderType::const_iterator it=order.begin();
               it!=order.end(); ++it) {
            os << *it << " ";
          }
          os << "\n";
        }
        firstTime = false;
      }
      if (comm->Master()) {
        for (OrderType::const_iterator it=order.begin();
             it!=order.end(); ++it) {
          os << sci(data.at(*it)) << " ";
        }
        os << "\n";
        if (numberOfSamples%flushFrequency==0) os << std::flush;
      }
#else
      if (firstTime) {
        if (comm->Master()) {
          os << "# ";
          for (const_iterator it=data.begin(); it!=data.end(); ++it) {
            os << it->first << " ";
          }
          os << "\n";
        }
        firstTime = false;
      }
      if (comm->Master()) {
        for (const_iterator it=data.begin(); it!=data.end(); ++it) {
          os << sci(it->second) << " ";
        }
        os << "\n";
        if (numberOfSamples%flushFrequency==0) os << std::flush;
      }
#endif
    }
    inline void increment() { numberOfSamples++; }
    inline int getNumberOfSamples() const { return numberOfSamples; }
    inline void clear() { numberOfSamples=0; data.clear(); names.clear(); }
    inline void setFlushFrequency(const int ff) { flushFrequency=ff; }
    inline int getFlushFrequency() const { return flushFrequency; }
  };

}  // namespace DGM

#endif // DGM_STATISTICS_HPP
