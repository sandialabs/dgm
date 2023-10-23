#ifndef CMC_RAM_DISK_HPP
#define CMC_RAM_DISK_HPP

/** \file RamDisk.hpp
    \brief CMC Ram Disk class
    \author Scott Collis
    \copyright (c)2003 Rice University
    \copyright (c)2014 Sandia National Laboratories
*/

namespace CMC {

  /// An initial attempt at in-core storage that mimics file-IO
  /** \note This is under construction and not ready for use. */
  template <class Scalar=double, class Ordinal=int>
  class RamDisk {

    Ordinal len;     ///< the length of the data
    Scalar *data;    ///< the actual data

  public:

    /// Constructor
    RamDisk( size_t s ) : len(s), data(0) {
      cout << "Beginning RamDisk allocation" << endl;
      data = new Scalar[len];
      for (Ordinal i=0; i<len; i++) {
        data[i] = i;
      }
      cout << "Finished allocating RamDisk" << endl;
    }

    /// Destructor
    ~RamDisk() {
      cout << "Removing RamDisk" << endl;
      if (data) delete[] data;
    }

    /// Returns the size of the RamDisk
    Ordinal size() const { return len; }

  };

}

#endif // CMC_RAM_DISK_HPP
