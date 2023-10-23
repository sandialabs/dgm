#ifndef DGM_BOUNDARY_HPP
#define DGM_BOUNDARY_HPP

/** \file Boundary.hpp
    \brief Boundaries on which boundary conditions are applied
    \author Scott Collis
*/

#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

// DGM includes
#include "Comm.hpp"
#include "Partition.hpp"
#include "Side.hpp"
#include "Element.hpp"

namespace DGM {

/// Boundary class
/** Each Field will have a std::vector<Boundary> that defines the boundary
    side and associated boundary conditions for that Field.  I want to make
    the boundary class as generic as possible so that it can be used for a
    variety of problems. */
class Boundary {

  // smart pointers
  typedef DGM::Shared<Side>::Ptr SidePtr;
  typedef DGM::Shared<Element>::Ptr ElmtPtr;

  typedef DGM::Size GlobalSize;
  typedef DGM::Ordinal LocalSize;

 public:
  LocalSize  id;                  // Boundary identification number
  GlobalSize geid;                // Global element id
  LocalSize  eid;                 // Local element id
  string     type;                // Boundary type
  LocalSize  sid;                 // Side id boundary conditions are for

  Element    *elmt;               // Boundary is on this element
  Side       *S;                  // Element Internal state side
  Side       *B;                  // Boundary condition side
  Side       *side;               // Pointer to side holding boundary condition
  Side       *V;                  // Boundary condition values that are
                                  //   perserved from step to step.

  template <typename T>
  static T undefined() { return numeric_limits<T>::max(); }

  template <typename T>
  static bool undefined(const T id) { return id==undefined<T>(); }

  /// Default constructor
  Boundary();

  /// Normal constructor
  Boundary(Partition<Size,Ordinal,Scalar>::Ptr, const LocalSize ID,
           const vector<Element*> &el, ifstream &in);

  // destructor
  ~Boundary();

  // methods
  void read(ifstream &in);
  void write(ofstream &out) const;

  void Abs() {
    if (S) S->u.Abs();
    if (B) B->u.Abs();
  }

  void zero() {
    if (S) S->u = 0;
    if (B) B->u = 0;
    if (V) V->u = 0;
  }

  size_t size() const {
    assert( S->qtot() == B->qtot() );
    return S->qtot();
  }

};

} // namespace DGM

#endif // DGM_BOUNDARY_HPP
