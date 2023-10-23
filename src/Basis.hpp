#ifndef DGM_BASIS_HPP
#define DGM_BASIS_HPP

/** \file Basis.hpp
    \brief This header file contains the definitions for the DGM Basis
    \author Scott Collis

    The basis definitions and notation follows that described in: George Em
    Karniadakis and Spencer J. Sherwin, Spectral/hp element methods for
    CFD, Oxford University Press, 1999.

    The bases are constructed similar to that done in Nektar++ using the 
    Polylib library for evaluating Legendre and Jacobi polynomials as well 
    as for computing appropriate quadrature weights and coordinates in the 
    master element coordinates \f$(a,b,c)\f$.  Note that Nektar++ and Polylib 
    are used under an MIT license as described in License.txt.

    Herein, we use \f$w\f$ for weights and \f$w\f$ for coordinates on the 
    domain \f$[-1:1]\f$ as in Polylib and we denote the associated intervals 
    in the master element coordinates as \f$za\f$, \f$zb\f$, and \f$zc\f$ 
    throughout.

    The nodal basis definitions follow that described in:
    Jan S. Hesthaven and Tim Warburton, "Nodal Discontinuous Galerkin Methods"
    Springer, 2008.
*/

// system includes
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

// DGM includes
#include "Types.hpp"
#include "Constants.hpp"
#include "Polylib.hpp"

namespace DGM {

/// Matrix information class
class Minfo {
 public:
  typedef DGM::Shared<Minfo>::Ptr Ptr;  ///< shared pointer
  dMatrix mat;                          ///< Matrix data
  intVector pivots;                     ///< Vector of pivots
};

/// Define to use an orthonormal basis
/** This only gives diagonal mass-matrices for elements with constant Jacobian.
    \warning be careful with restart files if you switch this! */
#define DGM_BASIS_NORM

/// Storage for a mode of a modal Basis
class Mode {
 public:
  typedef DGM::Shared<Mode>::Ptr Ptr;  ///< shared pointer
  dVector a;                           ///< a-coordinates
  dVector b;                           ///< b-coordinates
  dVector c;                           ///< c-coordinates
  dVector nt;                          ///< nodal tet & tri coordinates
};

/// Access base class for vertex modes of a modified Jacobi basis
class BaseVertMode {
public:
  typedef DGM::Shared<BaseVertMode>::Ptr Ptr;
  virtual ~BaseVertMode() {}
  virtual Mode operator()(const Ordinal id) const = 0;
};

/// Access base class for edge modes of a modified Jacobi basis
class BaseEdgeMode {
public:
  typedef DGM::Shared<BaseEdgeMode>::Ptr Ptr;
  virtual ~BaseEdgeMode() {}
  virtual Mode operator()(const Ordinal id, const Ordinal mode) const = 0;
};

/// Access base class for face modes of a modified Jacobi basis
class BaseFaceMode {
public:
  typedef DGM::Shared<BaseFaceMode>::Ptr Ptr;
  virtual ~BaseFaceMode() {}
  virtual Mode operator()(const Ordinal id,
                          const Ordinal i, const Ordinal j) const = 0;
};

/// Generic base class for Basis functions
/** Okay, this should be a generic class that can hold any number of basis
    types, but the current implementation holds an orthonormal Legendre basis
    appropriate for discontinuous Galerkin methods and a \f$C^0\f$ modified
    Jacobi basis that is required to handle curved elements.

    It can also hold a nodal basis for triangles and tetrahedra.

    \todo It would be good to really make this a base class and to then have
    each basis be a derived class.

    Herein, we use \f$w\f$ for weights and \f$z\f$ for coordinates on the domain 
    \f$[-1:1]\f$ as in Polylib and we denote the associated intervals in the 
    master element coordinates as \f$z_a\f$, \f$z_b\f$, and \f$z_c\f$
    throughout. We also use the symbol \f$q\f$ to denote the number of
    quadrature points with \f$q_a\f$ being the number of quadrature points
    in the \f$a\f$ direction.
*/
class Basis {

public:

  /// Types of primary Basis representations available
  enum Type {
    Lagrange,                 ///< Lagrange basis (nodal and spectral)
    Ortho                     ///< Orthogonal (e.g. Legendre) basis (modal)
  };

  /// \name Basis information
  //@{
  Ordinal L;                  ///< Number modes in each direction (L=p+1) 
  Ordinal nModes;             ///< Total number of modes in this Basis
  Type type;                  ///< Polynomial basis type
  //@}

  /// \name Quadrature information
  //@{
  Ordinal qa;                 ///< Quadrature order in the a-direction
  Ordinal qb;                 ///< Quadrature order in the b-direction
  Ordinal qc;                 ///< Quadrature order in the c-direction
  Ordinal qnt;                ///< Quadrature points for nodal Tet, Tri

  dVector wa;                 ///< Gauss weights in the a-direction
  dVector wb;                 ///< Gauss weights in the b-direction
  dVector wc;                 ///< Gauss weights in the c-direction
  dVector za;                 ///< Gauss coordinates in the a-direction
  dVector zb;                 ///< Gauss coordinates in the b-direction
  dVector zc;                 ///< Gauss coordinates in the c-direction

  dVector znt_r;              ///< r-coordinate of Nodal Tet & Tri quadrature
  dVector znt_s;              ///< s-coordinate of Nodal Tet & Tri quadrature
  dVector znt_t;              ///< t-coordinate of Nodal Tet quadrature
  //@}

  /// \name Modified Jacobi basis information
  //@{
  Ordinal nVerts;             ///< Number vertices
  Ordinal nEdges;             ///< Number of edges
  Ordinal nFaces;             ///< Number of faces
  Ordinal mFace;              ///< Modes per face
  Ordinal mIntr;              ///< Modes per interior
  DGM::Shared<BaseVertMode>::Ptr vm;  ///< pointer to vertex modes
  DGM::Shared<BaseEdgeMode>::Ptr em;  ///< pointer to edge modes
  DGM::Shared<BaseFaceMode>::Ptr fm;  ///< pointer to face modes
  dVector amem;               ///< Memory for Modifed Jacobi a-modes
  dVector bmem;               ///< Memory for Modifed Jacobi b-modes
  dVector cmem;               ///< Memory for Modifed Jacobi c-modes
  //@}

  /// \name Primary basis basis (Legendre for Ortho)
  //@{
  dVector mem;                ///< Actual memory for the Legendre basis
  std::vector<Mode> mode;     ///< Vector of all modes in primary basis
  dVector *ba;                ///< Legendre basis in the a-direction
  dVector *bbv;               ///< b-direction Legendre (for Quads and Hex)
  dMatrix *bb;                ///< b-direction Legendre (for Triangles)
  dVector *bc;                ///< c-direction Legendre (for Hex)
  dVector *bnt;               ///< NodalTri & NodalTet (not used elsewhere)

  // Matrix interface to primary modes
  dMatrix Ba;                 ///< CMC::Matrix for the a-modes
  dMatrix Bb;                 ///< CMC::Matrix for the b-modes
  dMatrix Bc;                 ///< CMC::Matrix for the c-modes
  dMatrix Bnt;                ///< CMC::Matrix for the NodalTri,tet-modes
  //@}

  /// \name Secondary basis (Lagrange for Ortho)
  //@{
  dVector *ga;                ///< Lagrange basis in the a-direction
  dVector *gbv;               ///< b-direction Lagrange (for Quads and Hex)
  dMatrix *gb;                ///< b-direction Lagrange (for Triangles)
  dVector *gc;                ///< c-direction Lagrange (for Hex)

  // Matrix interface to secondary modes
  dMatrix Ga;                 ///< CMC::Matrix for the a-modes
  dMatrix Gb;                 ///< CMC::Matrix for the b-modes
  dMatrix Gc;                 ///< CMC::Matrix for the c-modes

  // Vandermonde storage
  Minfo Vi;                   ///< Inverse Vandermonde matrix
  //@}

  /// Constructor
  Basis(const Ordinal L_, const Ordinal q_a, const Ordinal q_b,
        const Ordinal q_c, const Ordinal N_modes, const Ordinal q_nt=0);

  // Should have copy constructor and operator=()

  /// Destruct the modal storage -- very carefully
  ~Basis() {
    // cout<<"~Basis()"<<endl;
    if (ba) delete[] ba;
    if (bbv) delete[] bbv;
    if (bb) delete[] bb;
    if (bc) delete[] bc;
    if (bnt) delete[] bnt;
    if (ga) delete[] ga;
    if (gbv) delete[] gbv;
    if (gb) delete[] gb;
    if (gc) delete[] gc;
  }

  /// Access function for vertex modes
  Mode vertMode(const Ordinal id) const { return (*vm)(id); }

  /// Access function for edge modes
  Mode edgeMode(const Ordinal id, const Ordinal mode) const {
    return (*em)(id,mode);
  }

  /// Access function for face modes
  Mode faceMode(const Ordinal id, const Ordinal i, const Ordinal j) const {
    return (*fm)(id,i,j);
  }

  /// Generate the Lagrange basis
  static dVector *make_Lagrange(const Ordinal, dVector &);

  /// Generate the Legendre basis (matrix form)
  static void make_Legendre(const int der, const Ordinal L, const Ordinal q,
                            const dVector &z, dMatrix &B);
  /// Generate the Legendre basis (vector form)
  static dVector *make_Legendre(const int der, const Ordinal L, const Ordinal Q,
                                const dVector &z);

#ifdef DGM_VECTOR_DUBINER
  /// Generate the Dubiner basis
  static dVector **make_Dubiner (const Ordinal L, const Ordinal Q, dVector &z);
#else
  /// Generate the Dubiner basis
  static dMatrix *make_Dubiner (const Ordinal L, const Ordinal Q, dVector &z);
#endif
  /// Generate the nodal basis on triangles
  static dVector *make_NodalTri(const Ordinal L, const Ordinal nModes,
                                dVector &zr, dVector &zq);
  /// Generate the nodal basis on Tetrahedra
  static dVector *make_NodalTet(const Ordinal L,
                                const Ordinal nModes,
                                dVector &r,
                                dVector &s,
                                dVector &t);
};

/// Database of Basis used to manage multiple Basis objects
/** Each element has it's own basis database. */
class BasisDB {
public:
  map<string,Basis*> bases;   ///< Implemented as an STL map
  typedef map<string,Basis*>::iterator iterator;
  /// destructor
  ~BasisDB() {
    for ( map<string,Basis*>::iterator basis = bases.begin();
          basis != bases.end(); basis++ ) {
      delete basis->second;
    }
  }
};

/// Interpolation class
class Interp {
public:
  /// Types of interpolations currently supported
  enum Type {
    G2GL,                     ///< Gauss to Gauss-Lobatto
    GL2G,                     ///< Gauss-Lobatto to Gauss
    GRJ2G,                    ///< Gauss-Radau-Jacobi to Gauss
    G2GRJ,                    ///< Gauss to Gauss-Radau-Jacobi
    G2U,                      ///< Gauss to Uniform
    GL2U,                     ///< Gauss-Lobatto to Uniform
    GRJ2U,                    ///< Gauss-Radau-Jacobi to Uniform
    GL2GL,                    ///< Gauss-Lobatto to Gauss-Lobatto
    GL2M2GL,                  ///< Gauss-Lobatto to Modal to Gauss-Lobatto
    G2M2GL,                   ///< Gauss to Modal to Gauss-Lobatto
    GL2M,                     ///< Gauss-Lobatto to Modal 
    M2GL                      ///< Modal to Gauss-Lobatto
  };
};

//============================================================================
//          I n t e r p o l a t i o n   M a t r i x   D a t a b a s e
//============================================================================

/// Helper class for Interpolation Matrix database
/** This std::map based database seems to work well although it might be
    better to use a hash_map in the future.  I also may be able to do a
    better job of "finding" an entry by caching the previous value.  I bet
    many times this would immediately find the correct entry. */
class IMinfo {
  const Interp::Type type;       ///< Interpolation type (from-to)
  const Ordinal qa;              ///< Quadrature order in the a-direction
  const Ordinal qb;              ///< Quadrature order in the b-direction
  const Ordinal qc;              ///< Quadrature order in the c-direction
public:
  /// Constructor
  IMinfo( Interp::Type t, Ordinal a, Ordinal b, Ordinal c=0 ) :
    type(t), qa(a), qb(b), qc(c)
  { }
  /// Map needs an equality operator
  friend int operator== (const IMinfo &a, const IMinfo &b) {
    return a.type==b.type && a.qa==b.qa && a.qb==b.qb && a.qc==b.qc;
  }
  /// Map needs the less-than operator to keep its elements sorted
  friend int operator< (const IMinfo &a, const IMinfo &b) {
    if (a.type < b.type) {
      return 1;
    } else {
      if (a.type == b.type) {
        if (a.qa < b.qa) {
          return 1;
        } else {
          if (a.qa == b.qa) {
            if (a.qb < b.qb) {
              return 1;
            } else {
              if (a.qb == b.qb) {
                if (a.qc < b.qc) return 1;
              }
            }
          }
        }
      }
    }
    return 0;
  }
};

/// Interpolation Matrix database
class IMDB {
public:
  /// Database implemented as a std::map
  std::map<IMinfo,dMatrix*> entry;
  /// Iterator for this database
  typedef map<IMinfo,dMatrix*>::iterator iterator;
  /// Destructor loops over entries and deletes matrix
  ~IMDB() {
    for ( iterator e = entry.begin(); e != entry.end(); e++ )
      delete e->second;
  }
};

//============================================================================
//           D e r i v a t i v e   M a t r i x   D a t a b a s e
//============================================================================

/// Derivative matrix holds the derivative matrix operators for an element
class Dinfo {
public:
  /// Shared pointer to a derivative matrix
  typedef DGM::Shared<Dinfo>::Ptr Ptr;
  /// Derivative matrix in the 'a' direction
  dMatrix Da;
  /// Derivative matrix in the 'b' direction
  dMatrix Db;
  /// Derivative matrix in the 'c' direction
  dMatrix Dc;
  /// Derivative matrix in the 'r' direction for nodal triangle basis
  dMatrix Dr;
  /// Derivative matrix in the 's' direction for nodal triangle basis
  dMatrix Ds;
  /// Derivative matrix in the 't' direction for nodal triangle basis
  dMatrix Dt;
  /// Transpose of the derivative matrix in the 'a' direction
  dMatrix Dat;
  /// Transpose of the derivative matrix in the 'b' direction
  dMatrix Dbt;
  /// Transpose of the derivative matrix in the 'c' direction
  dMatrix Dct;
  /// Transpose of the derivative matrix in the 'r' direction
  dMatrix Drt;
  /// Transpose of the derivative matrix in the 's' direction
  dMatrix Dst;
  /// Transpose of the derivative matrix in the 't' direction
  dMatrix Dtt;
  /// Default constructor
  Dinfo() { };
  /// Copy constructor
  Dinfo(Dinfo *D) :
    Da(D->Da), Db(D->Db), Dc(D->Dc), Dr(D->Dr), Ds(D->Ds), Dt(D->Dt),
    Dat(D->Dat), Dbt(D->Dbt), Dct(D->Dct), Drt(D->Drt), Dst(D->Dst),
    Dtt(D->Dtt)  { };
  /// Deep copy constructor
  Dinfo(const Dinfo &D);
  bool operator==(const Dinfo &other) const {
    const bool eq =
         Da  == other.Da
      && Db  == other.Db
      && Dc  == other.Dc
      && Dr  == other.Dr
      && Ds  == other.Ds
      && Dat == other.Dat
      && Dbt == other.Dbt
      && Dct == other.Dct
      && Drt == other.Drt
      && Dst == other.Dst;
    return eq;
  }
  bool operator!=(const Dinfo &other) const {
    return (!(*this == other));
  }
};

/// Deep copy constructor
inline Dinfo::Dinfo(const Dinfo &D) :
  Da (D.Da.rows(),   D.Da.cols()),
  Db (D.Db.rows(),   D.Db.cols()),
  Dc (D.Dc.rows(),   D.Dc.cols()),
  Dr (D.Dr.rows(),   D.Dr.cols()),
  Ds (D.Ds.rows(),   D.Ds.cols()),
  Dat(D.Dat.rows(),  D.Dat.cols()),
  Dbt(D.Dbt.rows(),  D.Dbt.cols()),
  Dct(D.Dct.rows(),  D.Dct.cols()),
  Drt(D.Drt.rows(),  D.Drt.cols()),
  Dst(D.Dst.rows(),  D.Dst.cols()) {
  Da  = D.Da;
  Db  = D.Db;
  Dc  = D.Dc;
  Dr  = D.Dr;
  Ds  = D.Ds;
  Dat = D.Dat;
  Dbt = D.Dbt;
  Dct = D.Dct;
  Drt = D.Drt;
  Dst = D.Dst;
 }

/// Entry Class for the Derivative Matrix database
class Dentry {
  Ordinal qa;       ///< Quadrature order in the a-direction
  Ordinal qb;       ///< Quadrature order in the b-direction
  Ordinal qc;       ///< Quadrature order in the c-direction
public:
  /// Constructor
  Dentry( Ordinal a, Ordinal b, Ordinal c=0 ) {qa=a; qb=b; qc=c;}
  /// Map needs a less-than operator to keep elements sorted
  friend int operator< (const Dentry &a, const Dentry &b) {
    if (a.qa < b.qa) {
      return 1;
    } else {
      if (a.qa == b.qa) {
        if (a.qb < b.qb) {
          return 1;
        } else {
          if (a.qb == b.qb) {
            if (a.qc < b.qc) return 1;
          }
        }
      }
    }
    return 0;
  }
  /// Every map entry needs an equality operator
  friend int operator== (const Dentry &a, const Dentry &b) {
    return a.qa==b.qa && a.qb==b.qb && a.qc==b.qc;
  }
};

/// Derivative Matrix database
class DerivDB {
public:
  /// Database is implemented as an std:map
  std::map<Dentry,Dinfo::Ptr> entry;
  /// Interator type for the Derivative Matrix database
  typedef map<Dentry,Dinfo::Ptr>::iterator iterator;
  /// destructor loops over entries and deletes matrix
  ~DerivDB() {
    //cout << "~DerivDB" << endl;
    //for ( iterator e = entry.begin(); e != entry.end(); e++ )
    //  delete e->second;
  }
};

/// Entry class for the Vandermonde Matrix database
class VandermondeEntry {
  Ordinal nModes;
public:
  VandermondeEntry(Ordinal nm) : nModes(nm) {}
  friend int operator< (const VandermondeEntry &a, const VandermondeEntry &b) {
    if (a.nModes < b.nModes) return 1;
    return 0;
  }
  friend int operator== (const VandermondeEntry &a, const VandermondeEntry &b) {
    return a.nModes==b.nModes;
  }
};

/// Vandermonde Matrix database
class VandermondeDB {
public:
  std::map<VandermondeEntry,Minfo::Ptr> entry;
  typedef map<VandermondeEntry,Minfo::Ptr>::iterator iterator;
  ~VandermondeDB() {}
};

} // namespace DGM

#endif  // DGM_BASIS_HPP
