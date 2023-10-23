/** \file CuttingPlanes.hpp
    \brief Define cutting planes
    \author K. Noel Belcourt
*/

#ifndef DGM_CuttingPlanes_hpp
#define DGM_CuttingPlanes_hpp

// standard libraries
#include <ostream>

// DGM libraries
#include "Cartesian.hpp"
#include "CutPlane.hpp"

namespace DGM {

template <typename Scalar>
struct cutting_planes : cutting_plane<Scalar> {
  typedef cutting_plane<Scalar> Base;

  cutting_planes() : left(0), right(0) {
  }

  cutting_planes(axis x, Scalar r) :
    Base(x, r), left(0), right(0) {}

  ~cutting_planes() {
    delete left;
    delete right;
    left = right = 0;
  }

  cutting_planes *left, *right;

private:
  cutting_planes(const cutting_planes&);
  cutting_planes& operator=(const cutting_planes&);
};

template <typename Scalar>
void swap_nodes(cutting_planes<Scalar>& c) {
  cutting_planes<Scalar>* tmp = c.left;
  c.left = c.right;
  c.right = tmp;
}

template <typename Scalar>
cutting_planes<Scalar>&
find_insertion_point(Scalar p, cutting_planes<Scalar>* c) {
  // find insertion point
  while (1) {
    if (c->left)
      if (p < c->left->p)
        c = c->left;
      else if (p == c->left->p) {
        c = c->left;
        break;
      }
      else break;
    else if (c->right)
      if (c->right->p < p)
        c = c->right;
      else if (p == c->right->p) {
        c = c->right;
        break;
      }
      else break;
    else break;
  }
  assert (0 != c);
  return *c;
}

template <typename Scalar>
cutting_planes<Scalar>*
add_child(axis a, Scalar p, cutting_planes<Scalar>& cp) {
  cutting_planes<Scalar>& c = cp; // find_insertion_point(p, &cp);

  // insert into c
  cutting_planes<Scalar>* child = 0;
  if (c.left && p == c.left->p) {
    // already a child node, swap into place
    child = c.left;
  }
  else if (c.right && p == c.right->p) {
    // already a child node, swap into place
    child = c.right;
  }
  else {
    child = new cutting_planes<Scalar>(a, p);
    if (p < c.p) c.left = child;
    else c.right = child;
  }

  // invariant
  assert (0 != child);
  // assert ((p < c.p && p == c.left->p) || (c.p < p && p == c.right->p));
  return child;
}

template <typename Scalar>
std::ostream& operator<<(std::ostream& ofp, const cutting_planes<Scalar>& c) {
  std::string s = "  ";
  ofp << "cut plane on axis " << c.a << " at location " << c.p;
  if (c.left) {
    ofp << "\n" << s << "left is ";
    print(ofp, *c.left, s);
  }
  if (c.right) {
    ofp << "\n" << s << "right is ";
    print(ofp, *c.right, s);
  }
  return ofp;
}

template <typename Scalar>
std::ostream& print(std::ostream& ofp, const cutting_planes<Scalar>& c, std::string s) {
  ofp << "cut plane on axis " << c.a << " at location " << c.p;
  s += "  ";
  if (c.left) {
    ofp << "\n" << s << "left is ";
    print(ofp, *c.left, s);
  }
  if (c.right) {
    ofp << "\n" << s << "right is ";
    print(ofp, *c.right, s);
  }
  return ofp;
}

}  // namespace DGM

#endif
