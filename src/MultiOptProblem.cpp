#ifdef DGM_PARALLEL

#include "MultiOptProblem.hpp"

/** \file MultiOptProblem.cpp
    \brief Multiple Optimal Control Problem implementation
    \author Joe Young
    \author Scott Collis
*/

namespace DGM {

namespace Multi {

/** Returns the smallest group size given the total number of objects
    divided between the specified number of groups. */
int get_smallest(int total,int ngroups){
  return total/ngroups;
}

/// Returns the largest group size
int get_largest(int total,int ngroups){
  // The smallest size group
  int m=get_smallest(total,ngroups);
  return total%ngroups==0 ? m : m+1;
}

/** Returns the number of groups that contain extra objects (the largest
    group size). */
int get_extra(int total,int ngroups){
  return total%ngroups;
}

/// Given an id to an object, determine which group this object belongs
int get_group(int total,int ngroups,int id){
  // Get the smallest group, the largest, and the number of groups with
  // extra items
  int m=get_smallest(total,ngroups);
  int n=get_largest(total,ngroups);
  int p=get_extra(total,ngroups);

  // The group number
  return id<=n*p ? id/n : (id-n*p)/m+p;
}

/// Given an id to an object, determine the id to the head of the group
int get_head(int total,int ngroups,int id){
  // Get the smallest group, the largest, and the number of groups with
  // extra items
  int m=get_smallest(total,ngroups);
  int n=get_largest(total,ngroups);
  int p=get_extra(total,ngroups);

  // Get the group number
  int g=get_group(total,ngroups,id);

  // Calculate the head of the group
  return g<p ? g*n : (g-p)*m+n*p;
}

/** Given an id to an object, determine the number of objects in that id's
    group. */
int get_num_in_group(int total,int ngroups,int id){
  // Get the smallest group, the largest, and the number of groups with
  // extra items
  int m=get_smallest(total,ngroups);
  int n=get_largest(total,ngroups);
  int p=get_extra(total,ngroups);

  // Get the group number
  int g=get_group(total,ngroups,id);

  // Calculate the number in the group
  return g<p ? n : m;
}

/// Divides some integer between groups as evenly as possible
int divide_groups(int total,int ngroups,int id){
  // Determine the base number of items in each group
  int base=total/ngroups;

  // Determine if this particular group requires an additional element
  int offset= id < total-base*ngroups ? 1 : 0;

  // Return the sum of the base and the offset
  return base+offset;
}

}  // namespace Multi

}  // namespace DGM

#endif  // DGM_PARALLEL
