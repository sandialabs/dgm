#ifndef DGM_MEMORY_HPP
#define DGM_MEMORY_HPP

/** \file Memory.hpp
    \brief Provides platform independent interface to memory system queries
    \author Scott Collis

    Note that this capability does require the explicit use of platform
    specific function calls.  It is currently enabled for both Linux and Apple
    (Darwin) operating systems.  If, for example, you would want to use this
    on Windows, then specific function calls and defines would need to be
    implemented for that platform.

    Currently this uses the system approved defines to determine what platform
    the build is for.  Note that if you are cross-compiling, this may not be
    the case.
*/

// System includes
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <exception>
#include <stdint.h>
#include <string>
#include <fstream>
#include <streambuf>
#ifdef __APPLE__
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <mach/host_info.h>
#include <mach/mach_host.h>
#elif __linux__
#include <sys/sysinfo.h>
#endif
using namespace std;

// DGM includes
#include "Comm.hpp"
#include "Utilities.hpp"

#ifdef DGM_USE_HWLOC
#include <hwloc.h>
#endif

#include <boost/lexical_cast.hpp>

namespace DGM {

  /// DGM interface to the system-level memory
  /** This class provides a platform independent means of querying the
      system memory system to determine the amount of available core memory
      in hardware, the core memory still available and the maximum core
      memory used. */
  class Memory {

    unsigned verbose;                 ///< Verbosity flag

    const DGM::Comm::Ptr comm;        ///< DGM communicator

    mutable uint64_t highwater;       ///< High water mark for memory used

    string units;                     ///< Holds units designation

    uint64_t mem_unit;                ///< units/byte

  public:

    /// Constructor
    Memory( const string units_ = "Mb", const unsigned verbose_ = 0,
            const DGM::Comm::Ptr comm_ = DGM::Comm::World ) :
      verbose(verbose_), comm(comm_), highwater(0),
      units(units_), mem_unit(1) {
      if (units=="bytes")
        mem_unit=1;
      else if (units=="Kb")
        mem_unit=1024;
      else if (units=="Mb")
        mem_unit=1024*1024;
      else if (units=="Gb")
        mem_unit=1024*1024*1024;
      else
        comm->error("Illegal units passed to DGM::Memory");
      highwater = used();
    }

    /// Accessor for units
    string get_units() const { return units; }

    /// Accessor for mem_unit
    double get_mem_unit() const { return mem_unit; }

    /// Returns the hardware memory available
    uint64_t hwmem() const {
#ifdef __APPLE__
      int mib[2] = { CTL_HW, HW_MEMSIZE };
      u_int namelen = sizeof(mib) / sizeof(mib[0]);
      uint64_t size;
      size_t len = sizeof(size);
      if (sysctl(mib, namelen, &size, &len, NULL, 0) < 0) {
        perror("sysctl");
        comm->error("Exiting DGM");
      } else {
        comm->cout() << "Hardware memory size = " << size/1024/1024
                     << " MB"<<endl;
      }
      used();
      return size;
#elif __linux__
      struct sysinfo myinfo;
      uint64_t total_bytes;
      sysinfo(&myinfo);
      total_bytes = myinfo.mem_unit * myinfo.totalram;
      if (verbose) {
        comm->cout() << "Totalram = " << myinfo.totalram << endl;
        comm->cout() << "Freeram = " << myinfo.freeram << endl;
        comm->cout() << "Totalhigh = " << myinfo.totalhigh << endl;
        comm->cout() << "Freehigh = " << myinfo.freehigh << endl;
        comm->cout() << "mem_unit = " << myinfo.mem_unit << endl;
        comm->cout() << "Hardware memory size = " << total_bytes/(1ULL<<20)
                     << " MB" << endl;
      }
      used();
      return total_bytes;
#endif
    }

    /// Return available memory on the system
    uint64_t avail() const {
#ifdef __APPLE__
      vm_statistics_data_t page_info;
      vm_size_t pagesize;
      mach_msg_type_number_t count;
      kern_return_t kret;
      pagesize = 1;
      host_page_size(mach_host_self(), &pagesize);
      count = HOST_VM_INFO_COUNT;
      kret = host_statistics(mach_host_self(), HOST_VM_INFO,
                             (host_info_t)&page_info, &count);
      if (kret == KERN_SUCCESS) {
        uint64_t pw, pa, pi, pf, pu;
        pw = (uint64_t)page_info.wire_count*(uint64_t)pagesize;
        pa = (uint64_t)page_info.active_count*(uint64_t)pagesize;
        pi = (uint64_t)page_info.inactive_count*(uint64_t)pagesize;
        pf = (uint64_t)page_info.free_count*(uint64_t)pagesize;
        pu = pw+pa; // +pi;  // don't use inactive in used
        highwater = (pu > highwater) ? pu : highwater;
        if (verbose>1) {
          comm->cout()<<"Apple version of Memory::avail() details"<<endl;
          comm->cout()<<"pagesize  = "<<pagesize<<endl;
          comm->cout()<<"pw  = "<<pw<<endl;
          comm->cout()<<"pa  = "<<pa<<endl;
          comm->cout()<<"pi  = "<<pi<<endl;
          comm->cout()<<"pf  = "<<pf<<endl;
          comm->cout()<<"pu  = "<<pu<<endl;
        }
  if (verbose)
          comm->cout()<<"Total available main memory is "
                      <<pf/1024/1024<<" MB"<<endl;
        return pf+pi;  // inactive is really available so inclue it
      } else {
        throw DGM::exception("DGM::Memory::avail() Error in kernel query");
        return 0;
      }
#elif __linux__
#ifdef DGM_LINUX_USE_SYSINFO
      struct sysinfo myinfo;
      uint64_t total_bytes;
      sysinfo(&myinfo);
      total_bytes = myinfo.mem_unit * ( myinfo.freeram + myinfo.freehigh +
                                        myinfo.bufferram );
#else
      ifstream proc("/proc/meminfo");
      string token;
      while (token != "MemFree:" )
        if (!(proc>>token))
          throw DGM::exception("Memory could not find MemFree: token.");
      uint64_t memfree(0);
      if (!(proc>>memfree))
        throw DGM::exception("Memory::avail could not read memfree value.");
      while (token != "Cached:" )
        if (!(proc>>token))
          throw DGM::exception("Memory could not find Cached: token.");
      uint64_t cached(0);
      if (!(proc>>cached))
        throw DGM::exception("Memory::avail could not read cached value.");
      uint64_t total_bytes = 1024 * (memfree + cached);
#endif
      if (verbose)
        comm->cout()<<"Total available main memory "<<total_bytes/(1ULL<<20)
                    <<" MB"<<endl;
      used();
      return total_bytes;
#endif
    }

    /// Return main memory used on the system
    uint64_t used() const {
#ifdef __APPLE__
      vm_statistics_data_t page_info;
      vm_size_t pagesize;
      mach_msg_type_number_t count;
      kern_return_t kret;
      pagesize = 0;
      host_page_size(mach_host_self(), &pagesize);
      count = HOST_VM_INFO_COUNT;
      kret = host_statistics(mach_host_self(), HOST_VM_INFO,
                             (host_info_t)&page_info, &count);
      if (kret == KERN_SUCCESS) {
        uint64_t pw, pa, pi, pu;
        pw = page_info.wire_count*pagesize;
        pa = page_info.active_count*pagesize;
        pi = page_info.inactive_count*pagesize;
        //unsigned long pf = page_info.free_count*pagesize;
        pu = pw+pa+pi;
        highwater = (pu > highwater) ? pu : highwater;
        if (verbose)
          comm->cout()<<"Total main memory used is "<<pu/1024/1024<<" MB"<<endl;
        return pu;
      } else {
        comm->error("DGM::Memory::used(): Error in kernel query");
        return 0;
      }
#elif __linux__
      struct sysinfo myinfo;
      uint64_t total_bytes;
      sysinfo(&myinfo);
      total_bytes = myinfo.mem_unit * (myinfo.totalram - myinfo.freeram);
      highwater = (total_bytes > highwater) ? total_bytes : highwater;
      if (verbose)
        comm->cout()<<"Total main memory used is "<<total_bytes/(1ULL<<20)
                    <<" MB"<<endl;
      return total_bytes;
#endif
    }

    /// Returns the maximum memory used as measured by this class
    /** Note that the max memory is only sampled when methods of this class
        are called so that it is quite likely that this is approximate at
        best. */
    uint64_t maxmemused() const {
      used();
      return highwater;
    }

    /// Use hwloc to get number of numa nodes, or return 0
    /// Note that this returns the total number of nodes on
    /// an SMP system.  The behavior of nnodes is likely to
    /// be different on a large distributed cluster.
    unsigned long nnodes() const {
      using std::max;
#ifdef DGM_USE_HWLOC
      hwloc_topology_t topology;
      hwloc_topology_init(&topology);
      hwloc_topology_load(topology);  // detection
      int num_numanodes = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_NUMANODE);
      int num_packages = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_PACKAGE);
      hwloc_topology_destroy(topology);
      return max(num_packages, num_numanodes);
#endif
      return 0;
    }

    /// Returns the number of cores per node
    unsigned long ncores() const {
#ifdef DGM_USE_HWLOC
      using std::max;
      hwloc_topology_t topology;
      hwloc_topology_init(&topology);
      hwloc_topology_load(topology);  // detection
      // int num_numanodes = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_NUMANODE);
      int num_logical_cores = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_PU);
      int num_packages = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_PACKAGE);
      // int num_cores = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_CORE);
      hwloc_topology_destroy(topology);
#if 0
      // document what we know about the architecture
      bool intel_hyperthreading_enabled = false;
      if (num_cores != num_logical_cores) {
        intel_hyperthreading_enabled = true;
      }
      bool on_smp_cluster = false;
      if (num_numanodes == num_packages) {
        on_smp_cluster = true;
      }
#endif
      // Apple helpfully returns 0 for number of physics packages
      // so we take max of numanodes and physical packages to get #nodes
      // num_packages = max(num_packages, num_numanodes);
      // function is documented to return cores per node
      return num_logical_cores / num_packages;
#elif __APPLE__
      //uint64_t numCPU;
      int numCPU;
      int mib[4];
      size_t len = sizeof(numCPU);

      /* set the mib for hw.ncpu */
      mib[0] = CTL_HW;
      mib[1] = HW_AVAILCPU;  // alternatively, try HW_NCPU;

      /* get the number of CPUs from the system */
      sysctl(mib, 2, &numCPU, &len, NULL, 0);

      if( numCPU < 1 ) {
        mib[1] = HW_NCPU;
        sysctl( mib, 2, &numCPU, &len, NULL, 0 );
        if( numCPU < 1 ) {
          numCPU = 1;
        }
      }
      return numCPU;
#elif __linux__
      return sysconf( _SC_NPROCESSORS_ONLN );
#endif
      return 0;
    }

    /// Output type sizes
    ostream & output_sizes(ostream &os) const {
      os << "sizeof(int) = " << sizeof(int) << endl;
      os << "sizeof(long) = " << sizeof(long) << endl;
      os << "sizeof(size_t) = " << sizeof(size_t) << endl;
      return os;
    }

    /// Output Memory information to a stream
    friend ostream & operator<<(ostream &os, const Memory &M) {
      os<<"Main memory hardware "<<M.hwmem()/M.mem_unit<<" "<<M.units<<endl;
      os<<"Main memory used "<<M.used()/M.mem_unit<<" "<<M.units<<endl;
      os<<"Main memory available "<<M.avail()/M.mem_unit<<" "<<M.units<<endl;
      os<<"Memory highwater mark "<<M.maxmemused()/M.mem_unit<<" "<<M.units;
      return os;
    }

  };

} // namespace DGM

#endif // DGM_MEMORY_HPP
