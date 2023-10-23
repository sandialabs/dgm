#ifndef DGM_BNDRY_STATS_HPP
#define DGM_BNDRY_STATS_HPP

/** \file BndryStats.hpp
    \brief Extracts the solution on a prescribed interelement boundary
    \author Scott Collis
*/

// system includes
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// DGM includes
#include "Comm.hpp"
#include "Mesh.hpp"
#include "Element.hpp"
#include "Side.hpp"
#include "Tri.hpp"
#include "Quad.hpp"
#include "Line.hpp"
#include "Boundary.hpp"

namespace DGM {

// forward declaration
class Field;

/// Boundary statistics
/** Extracts the solution along a set of prescribed edges and, optionally
    computes integral quantities such as lift and drag */
class BndryStats {

  const DGM::Comm::Ptr comm;  ///< Communicator for this BndryStats

  void read(const string &);  ///< Read the ".bnd" input file

 public:
  bool valid;                 ///< True if the BndryStats object is valid
  Field *F;                   ///< Local pointer to Field that owns the sides
  vector<Side*> sides;        ///< sides to extract statistics on
  vector<size_t> sorder;      ///< the order of each side

  /// Construct from root.bnd
  BndryStats(const string &root, Field *Fin);
  /// Construct from element and side vectors
  BndryStats(Field *Fin,
             const vector<Size> &elem,
             const vector<Ordinal> &side);

  /// Defines the types of output mesh the solution is extracted on
  enum Mesh {
    Collocation,   ///< use the native collocation mesh
    Uniform        ///< use a uniformly spaced mech
  };

  /// \name Local methods
  int size() const;
  void write(const string &);
  void get_coordinates(Coord &C, const Mesh=Collocation);
  void get_solution(dVector &u, const Mesh=Collocation);
  void get_coordinates(dVector &x, dVector &y, dVector &z,
                       const Mesh=Collocation);
  void get_solution_gradient(dVector &fx);
  void get_solution_gradient(dVector &fx, dVector &fy);
  void get_solution_gradient(dVector &fx, dVector &fy, dVector &fz);
  void compute(dVector &x, dVector &y, dVector &u);

  void gather( dVector &x, dVector &y, dVector &z, dVector &u,
               const Mesh=Collocation );

  void fill_sides(Field* fin);
  Scalar integrate(const Field* fin);
  Scalar area();
  Scalar average(const Field* fin);

  /// \name For EULER computations
  Scalar liftcalc(const dVector &p);
  Scalar dragcalc(const dVector &p);

  /// \name For Navier-Stokes computations
  Scalar liftcalc(const dVector &p,const dVector &tau11,const dVector &tau12);
  Scalar dragcalc(const dVector &p,const dVector &tau12,const dVector &tau22);

  /// \name For CO2 sequestration computations (Multi_Mat_Adv_Diff)
  Scalar flux_boundary_integral(const dVector&);
  Scalar flux_boundary_integral(const dVector&, const dVector&);
  Scalar flux_boundary_integral(const dVector&, const dVector&, const dVector&);
};

} // namespace DGM

#endif  // DGM_BNDRY_STATS_HPP
