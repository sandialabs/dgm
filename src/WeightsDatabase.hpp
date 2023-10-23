#ifndef DGM_WEIGHTS_DATABASE_HPP
#define DGM_WEIGHTS_DATABASE_HPP

/** \file WeightsDatabase.hpp
    \brief Graph weights database
    \author K. Noel Belcourt
*/

// System includes
#include <string>
#include <vector>

// DGM Includes
#include "Types.hpp"
#include "Topology.hpp"

namespace DGM {

/// A database for holding computational weights
/** The weights provide an estimate of the computational cost for a particular
    element to compute a particular physics so that one case load balance the
    computational for effectively. */ 
struct WeightsDatabase {

  /// file not found exception
  struct file_not_found {};

  /// invalid polynomial order exception
  struct invalid_porder {};

  /// scale factor
  Scalar scale;

  /// number of top-level groups
  int num_groups;

  /// minimum number of physics in database
  unsigned physics_min;

  /// maximum amount of data in database
  int size;

  /// physics offset as set by call to compute physics index
  int physics_index;

  /// database of values
  std::vector<int> values;

  /// physics and element names
  std::vector<std::string> p_names, e_names;

  // machine (hostname) specific weight file name
  WeightsDatabase();
  WeightsDatabase(std::string file_name, unsigned num_physics,
                  const int physics);
  WeightsDatabase(unsigned num_physics, const int physics,
                  std::vector<std::string>& p_names,
                  std::vector<std::string>& e_names);
  int get_index(unsigned p, Topology::ElementType e, bool is_affine,
                Ordinal porder);
  int get_index(Topology::ElementType e, bool is_affine, Ordinal porder);
  void add_weight(Topology::ElementType e, bool is_affine, Ordinal porder,
                  Scalar v);
  int get_weight(Topology::ElementType e, bool is_affine, Ordinal porder);
  void read(std::string file_name);
  void write(std::string file_name);
};

} // namespace DGM

#endif
