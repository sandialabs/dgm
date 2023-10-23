// Author: K. Noel Belcourt

// clang++ -DDGM_USE_HWLOC -I$DGM_TPL/hwloc/include
//   util/test_hwloc.cpp -L$DGM_TPL/hwloc/lib -lhwloc -lpciaccess -lxml2

#include <iostream>

#include <hwloc.h>

using std::cout;
using std::endl;

int main(int, char**) {
  hwloc_topology_t topology;
  hwloc_topology_init(&topology);
  hwloc_topology_load(topology);  // detection
  int num_numanode = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_NUMANODE);
  cout << "# numa nodes: " << num_numanode << endl;
  int num_pu = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_PU);
  cout << "# processor(logical) units: " << num_pu << endl;
  int num_package = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_PACKAGE);
  cout << "# physical packages: " << num_package << endl;
  int num_core = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_CORE);
  cout << "# cores: " << num_core << endl;
  hwloc_topology_destroy(topology);
  int cores_per_node = num_pu / num_numanode;
}
